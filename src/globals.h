#ifndef GLOBALS_H
#define GLOBALS_H

#include <assert.h>
#define ASSERT assert

#include <string>
#include <vector>

#include "modele_constants.h"
#include "experience_values.h"
#include "tableau.h"


extern const ModeleConstants modele_constants;
extern ExperienceValues experience_values;

SimulationValues create_etat_1750();
SimulationValues create_etat_2007();
SimulationValues create_etat_2000();

int modele_execute();


#endif //GLOBALS_H
