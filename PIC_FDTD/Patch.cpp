#include "Patch.h"

Patch::Patch(Parameters parametersList)
{
	localParametersList = parametersList;
	localParametersList.logMessages("Initialising patch...");
	particlesVector = VectorParticle(&localParametersList);
	mesh = Mesh(&localParametersList);
	mesh.checkMesh();
}

Patch::~Patch()
{
}

void Patch::startPIC()
{
	localParametersList.logMessages("Starting PIC loop...");
	for (int i = 0; i < localParametersList.maximumNumberOfIterations; i++)
	{
		ParticlePusher pusher();
		MCC collisions();
		ChargeProjector projector();
		FDTD fdtd();
		FieldSolver solver();
		FieldInterpolator interpolator();
	}
}