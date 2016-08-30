#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QTimerEvent>
#include <QObject>
#include <QTimer>
#include <QSettings>
#include <QFile>
#include <QEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    getsettings();
    dbcon(dataBaseName,dataBaseHost,dataBaseUserName,dataBaseUserPassword);

    if(isCenter != 0){
        startFilial();
    } else {
        startCenter();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::viewCenter()
{
    QSqlDatabase::database();
    QSqlRelationalTableModel *tableModel = new QSqlRelationalTableModel;
    tableModel->setTable("rise");
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tableModel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    tableModel->setRelation(1,QSqlRelation("menu","menuId","menuName"));
    tableModel->setRelation(2,QSqlRelation("users","userId","userName"));
    tableModel->select();



    tableModel->setHeaderData(1,Qt::Horizontal, QObject::trUtf8("Dish"));
    tableModel->setHeaderData(2,Qt::Horizontal, QObject::trUtf8("Resuarant"));
    tableModel->setHeaderData(3,Qt::Horizontal, QObject::trUtf8("Count"));
    tableModel->setHeaderData(6,Qt::Horizontal, QObject::trUtf8("Last Update"));


    ui->tableView->setModel(tableModel);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(4,true);
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(7,true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qDebug() << tableModel->query().lastQuery();
    qDebug() << QObject::trUtf8("Center Open UI");

}

void MainWindow::editFilial()
{
    QSqlDatabase::database();
    QSqlRelationalTableModel *tableModel = new QSqlRelationalTableModel;
    tableModel->setTable("rise");
    tableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableModel->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    tableModel->setRelation(1,QSqlRelation("menu","menuId","menuName"));
    tableModel->setRelation(2,QSqlRelation("users","userId","userName"));
    /* restId == userId */
    QString dataFilter = QString("%1'%2'").arg("rise.archive=false AND rise.userId=").arg(restId);
    tableModel->setFilter(dataFilter);
    tableModel->select();


    tableModel->setHeaderData(1,Qt::Horizontal, QObject::trUtf8("Dish"));
    tableModel->setHeaderData(2,Qt::Horizontal, QObject::trUtf8("Resuarant"));
    tableModel->setHeaderData(3,Qt::Horizontal, QObject::trUtf8("Count"));
    tableModel->setHeaderData(6,Qt::Horizontal, QObject::trUtf8("Last Update"));

    ui->tableView->setModel(tableModel);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(4,true);
    ui->tableView->setColumnHidden(5,true);
    ui->tableView->setColumnHidden(7,true);
    qDebug() << tableModel->query().lastQuery();

    qDebug() << QObject::trUtf8("Filial Open UI");


}

void MainWindow::startCenter()
{
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(viewCenter()));
    timerRise = new QTimer(this);
    connect(timerRise, SIGNAL(timeout()),this,SLOT(viewCenter()));
    timerRise->setInterval(timerMilliSeconds);
    timerRise->start();


}

void MainWindow::startFilial()
{
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(editFilial()));
    timerRise = new QTimer(this);
    connect(timerRise, SIGNAL(timeout()),this,SLOT(editFilial()));
    timerRise->setInterval(timerMilliSeconds);
    timerRise->start();
}


void MainWindow::getsettings()
{
            QString fileName = "./param.ini";
            QSettings *settings = new QSettings(fileName,QSettings::IniFormat);

            dataBaseName = settings->value("database/dataBaseName").toString();
            if(settings->value("database/dataBaseName").isNull()){
                settings->setValue("database/dataBaseName","rise");
            }
            qDebug() << "dataBaseName:" << dataBaseName;

            dataBaseHost = settings->value("database/dataBaseHost").toString();
            if(settings->value("database/dataBaseHost").isNull()){
                settings->setValue("database/dataBaseHost","127.0.0.1");
            }
            qDebug() << "dataBaseHost:" << dataBaseHost;

            dataBaseUserName = settings->value("database/dataBaseUserName").toString();
            if(settings->value("database/dataBaseUserName").isNull()){
                settings->setValue("database/dataBaseUserName","rise");
            }
            qDebug() << "dataBaseUserName:" << dataBaseUserName;

            dataBaseUserPassword = settings->value("database/dataBaseUserPassword").toString();
            if(settings->value("database/dataBaseUserPassword").isNull()){
                settings->setValue("database/dataBaseUserPassword","rise");
            }
            qDebug() << "dataBaseUserPassword:" << dataBaseUserPassword;


            restId = settings->value("restaurant/restId").toInt();
            if(settings->value("restaurant/restId").isNull()){
               settings->setValue("restaurant/restId",0);
            }
            qDebug() << "Restaurant ID:" << restId;

            isAdmin = settings->value("restaurant/isAdmin").toString();
            if(settings->value("restaurant/isAdmin").isNull()){
                settings->setValue("restaurant/isAdmin",0);
            }
            qDebug() << "isAdmin:" << isAdmin;

            isCenter = settings->value("restaurant/isCenter").toString();
            if(settings->value("restaurant/isCenter").isNull()){
                settings->setValue("restaurant/isCenter",0);
            }
            qDebug() << "isCenter:" << isCenter;

            timerMilliSeconds = settings->value("restaurant/timerMilliSeconds").toInt();
            if(settings->value("restaurant/timerMilliSeconds").isNull()){
                settings->setValue("restaurant/timerMilliSeconds",15000);
            }
            qDebug() << "timerMilliSeconds:" << timerMilliSeconds;

}

void MainWindow::dbcon(QString dataBaseName, QString dataBaseHost, QString dataBaseUserName, QString dataBaseUserPassword)
{
            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
            db.setHostName(dataBaseHost);
            db.setDatabaseName(dataBaseName);
            db.setUserName(dataBaseUserName);
            db.setPassword(dataBaseUserPassword);
            if (!db.open()){
                qDebug() << QObject::trUtf8("Database error connect") << db.lastError().text();
            }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == timerRise->timerId()){
            ++step;
           if(isCenter != 0){
              editFilial();
           } else {
              viewCenter();
           }
    } else {
            QObject::timerEvent(event);
    }
}
