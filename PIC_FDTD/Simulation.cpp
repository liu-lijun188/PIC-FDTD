//! \file
//! \brief Implementation of Simulation class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#include "Simulation.h"

// Default constructor
Simulation::Simulation()
{
}


// Constructor
Simulation::Simulation(Parameters *parametersList)
{
	parametersList->logMessages("Starting simulation", __FILE__, __LINE__);
	
	VectorPatch patchesVector(parametersList);
	patchesVector.startPIC();
}


// Destructor
Simulation::~Simulation()
{
}