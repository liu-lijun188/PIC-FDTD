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
Patch::Patch(Parameters *parametersList, int patchID)
{
	this->patchID = patchID;
	this->parametersList = *parametersList;
	parametersList->logMessages("Initialising patch " + std::to_string(patchID), __FILE__, __LINE__);
	mesh = Mesh(&this->parametersList);
	particlesVector = VectorParticle(&this->parametersList, &mesh, patchID);
	generateOutput(particlesVector.positionVector, mesh.numCells);
}

// Destructor
Patch::~Patch()
{
}

// Generate Tecplot output
void Patch::generateOutput(vector2D data, int N)
{
	parametersList.logMessages("Generating Tecplot output", __FILE__, __LINE__);
	writeMeshTecplot(tecplotMesh, mesh);
	writeSolutionXYTecplot(tecplotSolution, data, N);
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