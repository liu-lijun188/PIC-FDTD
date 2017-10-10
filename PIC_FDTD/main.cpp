//! \file
//! \brief Entry point into the PIC simulation
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Simulation.h"

int main()
{

	Parameters parametersList("inputs.txt");
	parametersList.distributeInputs();
	parametersList.printMemberVariables();

	Simulation simulation(parametersList);

	return 0;
}