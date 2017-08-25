#pragma once

#include "Parameters.h"
#include "Timer.h"
#include "VectorPatch.h"

class Simulation
{
public: 
	Simulation(Parameters parametersList);
	~Simulation();
	void loadBalance();
};