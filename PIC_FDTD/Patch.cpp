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
	//generateOutput(particlesVector.positionVector, mesh.numCells);
	generateOutput(tecplotSolution_T, particlesVector.positionVector, t);	// Single particle
}

// Destructor
Patch::~Patch()
{
}

// Generate Tecplot output
void Patch::generateOutput(std::string solutionName, vector2D data, double t)
{
	parametersList.logMessages("Generating Tecplot output", __FILE__, __LINE__);
	writeMeshTecplot(tecplotMesh, mesh);
	writeSolutionXY_T_Tecplot(solutionName, data, t);
}

// Start the PIC loop within a Patch object
void Patch::startPIC()
{
	parametersList.logMessages("Starting PIC loop in patch " + std::to_string(patchID), __FILE__, __LINE__);
	for (int i = 0; i < parametersList.maximumNumberOfIterations; i++)
	{
		t += parametersList.timeStep;
		ParticlePusher pusher(&parametersList, &mesh, &particlesVector);
		generateOutput(tecplotSolution_T, particlesVector.positionVector, t);
		MCC collisions();
		// ChargeProjector projector();
		// FDTD fdtd();
		// FieldSolver solver();
		// FieldInterpolator interpolator();
	}
}