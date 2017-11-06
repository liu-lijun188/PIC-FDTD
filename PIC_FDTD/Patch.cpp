//! \file
//! \brief Implementation of Patch class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Patch.h"

Patch::Patch()
{
}

Patch::Patch(Parameters parametersList, int patchID)
{
	this->patchID = patchID;
	localParametersList = parametersList;
	localParametersList.logMessages("Initialising patch " + std::to_string(patchID), __FILE__, __LINE__);
	particlesVector = VectorParticle(&localParametersList, patchID);
	mesh = Mesh(&localParametersList);
}

Patch::~Patch()
{
}

void Patch::startPIC()
{
	localParametersList.logMessages("Starting PIC loop in patch " + std::to_string(patchID), __FILE__, __LINE__);
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