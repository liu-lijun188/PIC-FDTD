#include "Simulation.h"

int main()
{

	Parameters parametersList("inputs.txt");
	parametersList.distributeInputs();
	parametersList.printMemberVariables();

	Simulation simulation(parametersList);

	return 0;
}