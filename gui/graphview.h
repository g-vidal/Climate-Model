#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QWidget>
#include <QComboBox>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_picker.h>

#include "globals.h"

class GraphView : public QWidget
{
    Q_OBJECT
public:
    GraphView(QWidget *parent = 0);

    void addNewCurve(int id);
    void setPosition(int position);
    void showCurve(int id);
    void hideCurve(int id);

public slots:
    void changeGraphType(int type);

private:
    QwtPlot plot;
    QList<QwtPlotCurve*> curves;
    QwtPlotPicker* picker;
    QComboBox graphType;

    tableau getDataForType(int id, int type);

};

#endif // GRAPHVIEW_H
