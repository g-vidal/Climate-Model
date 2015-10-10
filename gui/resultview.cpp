#include "resultview.h"
#include "graphview.h"

#include <QGridLayout>

ResultView::ResultView(QWidget *parent) :
    QWidget(parent)
{
    view.changeGraphType(TEMPERATURE);
    view1.changeGraphType(WATERLEVEL);
    view2.changeGraphType(CONCENTRATION_CO2);
    view3.changeGraphType(CALOTTESLEVEL);
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(&view,0,0);
    mainLayout->addWidget(&view1,0,1);
    mainLayout->addWidget(&view2,1,0);
    mainLayout->addWidget(&view3,1,1);
    this->setLayout(mainLayout);
}

void ResultView::startSimulation()
{
    experience_values.push_back_simulation();
    SimulationValues& sv = experience_values.back();
    sv.nom_simulation = sv.generate_name();
    modele_execute();
    view.addNewCurve(experience_values.nb_simulations()-1);
    view1.addNewCurve(experience_values.nb_simulations()-1);
    view2.addNewCurve(experience_values.nb_simulations()-1);
    view3.addNewCurve(experience_values.nb_simulations()-1);
}
