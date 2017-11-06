//! \file
//! \brief Implementation of Simulation class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Simulation.h"

Simulation::Simulation()
{
}

Simulation::Simulation(Parameters parametersList)
{
	parametersList.logMessages("Starting simulation", __FILE__, __LINE__);
	VectorPatch patchesVector(parametersList);
	patchesVector.startPIC();
}

Simulation::~Simulation()
{
}

void Simulation::loadBalance()
{
}