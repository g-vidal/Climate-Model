#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>

#include <QDebug>

#include "mainwindow.h"
#include "startview.h"
#include "graphview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    experience_values.set_etat_initial(create_etat_2007(),200);

    //init header
    QLabel* logo = new QLabel(this);
    logo->setPixmap(QPixmap("logo.png"));

    QPushButton* newSim = new QPushButton(tr("New Simulation"));
    QPushButton* addSim = new QPushButton(tr("Add Simulation"));
    QPushButton* save = new QPushButton(tr("Save"));
    QPushButton* load = new QPushButton(tr("Load"));
    QPushButton* quit = new QPushButton(tr("Quit"));

    QHBoxLayout* headerLayout = new QHBoxLayout;
    headerLayout->addWidget(logo);
    headerLayout->addWidget(&simuName);
    headerLayout->addStretch();
    headerLayout->addWidget(newSim);
    headerLayout->addWidget(addSim);
    headerLayout->addWidget(save);
    headerLayout->addWidget(load);
    headerLayout->addWidget(quit);

    QWidget* menuBar = new QWidget;
    menuBar->setLayout(headerLayout);

    //connect signal for header
    load->setShortcut(QKeySequence::Open);
    save->setShortcut(QKeySequence::Save);
    quit->setShortcut(QKeySequence::Quit);

    connect(newSim, SIGNAL(clicked()),this,SLOT(newSim()));
    connect(addSim,SIGNAL(clicked()),this,SLOT(addSim()));
    connect(load,SIGNAL(clicked()),this,SLOT(load()));
    connect(save,SIGNAL(clicked()),this,SLOT(save()));
    connect(quit,SIGNAL(clicked()),this,SLOT(quit()));
    //init startView

    //central widget
    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->setMenuBar(menuBar);
    centralLayout->addWidget(&startView);
    centralWidget.setLayout(centralLayout);
    setCentralWidget(&centralWidget);
}

void MainWindow::newSim()
{
    if(startView.isVisible())
    {
        qDebug()<<"visible";
        centralWidget.layout()->removeWidget(&startView);
        centralWidget.layout()->addWidget(&resultView);
    }
    resultView.startSimulation();
}

void MainWindow::addSim()
{

}

void MainWindow::load()
{

}

void MainWindow::save()
{

}

void MainWindow::quit()
{

}

MainWindow::~MainWindow()
{

}
