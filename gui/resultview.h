#ifndef RESULTVIEW_H
#define RESULTVIEW_H

#include <QWidget>

#include "graphview.h"

class ResultView : public QWidget
{
    Q_OBJECT
public:
    explicit ResultView(QWidget *parent = 0);
    void startSimulation();

private:
    GraphView view;
    GraphView view1;
    GraphView view2;
    GraphView view3;

};

#endif // RESULTVIEW_H
