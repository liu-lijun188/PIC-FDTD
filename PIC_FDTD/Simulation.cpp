#include "Simulation.h"

Simulation::Simulation(Parameters parametersList)
{
	parametersList.logMessages("Starting simulation...");
	VectorPatch patchesVector(parametersList);
	patchesVector.startPIC();
}

Simulation::~Simulation()
{
}

void Simulation::loadBalance()
{
}