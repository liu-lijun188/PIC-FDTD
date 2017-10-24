//! \file
//! \brief Entry point into the simulation
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Simulation.h"

int main()
{
	// Preprocessing of inputs
	Parameters parametersList("inputs.txt");	
	parametersList.assignInputs();				
	parametersList.processMesh();					 
	parametersList.printMemberVariables();

	// Commence simulation
	//Simulation simulation(parametersList);

	return 0;
}