//! \file
//! \brief Implementation of Patch class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#include "Patch.h"

// Default constructor
Patch::Patch()
{
}


// Constructor
Patch::Patch(Parameters *parametersList, int patchID)
{
	parametersList->logMessages("Initialising patch " + std::to_string(patchID), __FILE__, __LINE__);

	time = 0;
	this->patchID = patchID;
	this->parametersList = *parametersList;

	mesh = Mesh(&this->parametersList);
	particlesVector = VectorParticle(&this->parametersList, &mesh, patchID);

	generateOutput(tecplotSolution, particlesVector.positionVector, time);	
}


// Destructor
Patch::~Patch()
{
}


// Generate Tecplot output
void Patch::generateOutput(std::string solutionName, vector2D data, double time)
{
	parametersList.logMessages("Generating Tecplot output", __FILE__, __LINE__);

	writeMeshTecplot(tecplotMesh, mesh);
	writeSolutionXY_T_Tecplot(solutionName, data, 1, time);	// Currently for a single particle
}


// Start the PIC loop within a Patch object
void Patch::startPIC()
{
	parametersList.logMessages("Starting PIC loop in patch " + std::to_string(patchID), __FILE__, __LINE__);

	for (int i = 0; i < parametersList.maximumNumberOfIterations; i++)
	{
		time += parametersList.timeStep;

		ParticlePusher pusher(&parametersList, &mesh, &particlesVector);
		generateOutput(tecplotSolution, particlesVector.positionVector, time);
		
		// MCC collisions();

		ChargeProjector projector(&parametersList, &mesh, &particlesVector);
		
		// FDTD fdtd();
		// FieldSolver solver();
		// FieldInterpolator interpolator();
	}
}