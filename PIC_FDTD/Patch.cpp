//! \file
//! \brief Implementation of Patch class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Patch.h"

// Default constructor
Patch::Patch()
{
}

// Constructor
Patch::Patch(Parameters parametersList, int patchID)
{
	this->patchID = patchID;
	this->parametersList = parametersList;
	parametersList.logMessages("Initialising patch " + std::to_string(patchID), __FILE__, __LINE__);
	particlesVector = VectorParticle(&parametersList, patchID);
	mesh = Mesh(&parametersList);
}

// Destructor
Patch::~Patch()
{
}

// Start the PIC loop within a Patch object
void Patch::startPIC()
{
	parametersList.logMessages("Starting PIC loop in patch " + std::to_string(patchID), __FILE__, __LINE__);
	for (int i = 0; i < parametersList.maximumNumberOfIterations; i++)
	{
		ParticlePusher pusher();
		MCC collisions();
		ChargeProjector projector();
		FDTD fdtd();
		FieldSolver solver();
		FieldInterpolator interpolator();
	}
}