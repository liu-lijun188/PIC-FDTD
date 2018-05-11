//! \file
//! \brief Implementation of Simulation class 
//! \author Rahul Kalampattel
//! \date Last updated April 2018

#include "Simulation.h"

// Default constructor
Simulation::Simulation()
{
}


// Constructor
Simulation::Simulation(Parameters *parametersList)
{
	parametersList->logMessages("Starting simulation", __FILENAME__, __LINE__, 1);
	
	VectorPatch patchesVector(parametersList);
	patchesVector.startPIC();
	parametersList->numErrors = patchesVector.numErrors;

	parametersList->logMessages("Simulation complete", __FILENAME__, __LINE__, 1);
}


// Destructor
Simulation::~Simulation()
{
}