#include "Simulation.h"

Simulation::Simulation(Parameters parametersList)
{
	parametersList.logMessages("Starting simulation...");
	Timer newTimer;
	VectorPatch patchesVector(parametersList);
	patchesVector.startPIC();
}

Simulation::~Simulation()
{
}

void Simulation::loadBalance()
{
}