#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translation;
    translation.load("rise_ru_RU.qm");
    if(translation.isEmpty()){
        qDebug() << QObject::trUtf8("Do not find translation file");
    }
    a.installTranslator(&translation);
    MainWindow w;
    w.show();

    return a.exec();
}
