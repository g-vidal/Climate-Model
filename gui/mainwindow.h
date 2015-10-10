#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "resultview.h"
#include "startview.h"
#include "globals.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    ResultView resultView;
    StartView startView;
    QWidget centralWidget;
    QLabel simuName;


private slots:
    void save();
    void load();
    void addSim();
    void newSim();
    void quit();
};

#endif // MAINWINDOW_H
