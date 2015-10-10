#include "graphview.h"

#include <QVBoxLayout>

GraphView::GraphView(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(&graphType);
    layout->addWidget(&plot);

    plot.setAutoReplot(true);

    this->setLayout(layout);

    graphType.addItem(tr("Temperature (°C)"));
    graphType.addItem(tr("Sea Level (meter)"));
    graphType.addItem(tr("Calotte Latitude(degre)"));
    graphType.addItem(tr("CO2 Concentration (ppm)"));
    graphType.addItem(tr("CO2 Emission(Gt/yr)"));
    graphType.addItem(tr("Albedo (%)"));

    connect(&graphType,SIGNAL(currentIndexChanged(int)),this,SLOT(changeGraphType(int)));

}

void GraphView::addNewCurve(int id)
{
  QwtPlotCurve* curve = new QwtPlotCurve(experience_values.get_simulation(id).nom_simulation.c_str());
  curves.append(curve);
  curve->attach(&plot);
  changeGraphType(graphType.currentIndex());
}

void GraphView::setPosition(int position)
{

}

void GraphView::showCurve(int id)
{
    if(id < curves.size())
      curves.at(id)->setVisible(true);
}

void GraphView::hideCurve(int id)
{
    if(id < curves.size())
      curves.at(id)->setVisible(false);
}

void GraphView::changeGraphType(int type)
{
    graphType.setCurrentIndex(type);
    for(int i = 0; i < curves.size();i++)
    {
        tableau t = getDataForType(i,type);
        QVector<QPointF> data;
        double xoffset = experience_values.get_simulation(i).annee_debut;
        experience_values.indice_max();
        for(int j = 0; j < 100; j++)
        {
            double x = xoffset + j * experience_values.temps_elem();
            double y = t[j];
            data.append(QPointF(x,y));
        }
        curves.at(i)->setSamples(data);
    }
}

tableau GraphView::getDataForType(int id, int type)
{
    tableau data;
    switch(type)
    {
        case TEMPERATURE:
            data = experience_values.get_simulation(id).temperature_data;
        break;
        case WATERLEVEL:
            data = experience_values.get_simulation(id).niveau_mer_data;
        break;
        case CALOTTESLEVEL:
            data = experience_values.get_simulation(id).niveau_calottes_data;
        break;
        case CONCENTRATION_CO2:
            data = experience_values.get_simulation(id).concentrations_coo_data;
        break;
        case EMISSIONS_CO2:
            data = experience_values.get_simulation(id).emissions_coo_data;
        break;
        case ALBEDO:
            data = experience_values.get_simulation(id).albedo_data;
        break;
    }
    return data;
}
