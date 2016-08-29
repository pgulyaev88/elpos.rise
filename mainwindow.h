#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QTimerEvent>
#include <QObject>
#include <QTimer>
#include <QSettings>
#include <QFile>
#include <QEvent>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void viewCenter();
    void editFilial();

public slots:
    void getsettings();

private slots:
    void dbcon(QString dataBaseName, QString dataBaseHost, QString dataBaseUserName, QString dataBaseUserPassword);


private:
    Ui::MainWindow *ui;
    QString restName;
    int restId;
    int dishCode;
    QString dishName;
    QString dishCount;
    QString dataBaseName;
    QString dataBaseHost;
    QString dataBaseUserName;
    QString dataBaseUserPassword;
    QString fileName;
    QString isAdmin;
    QString isCenter;


};

#endif // MAINWINDOW_H
