#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("ENS","Climate-Model");
    settings.value("lang","en");

    MainWindow w;
    w.setWindowTitle("Climate-Model");
    w.showMaximized();

    return a.exec();
}
