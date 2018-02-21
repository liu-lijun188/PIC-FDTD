//! \file
//! \brief Implementation of Patch class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

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

	generateOutput(tecplotSolution, particlesVector.positionVector, particlesVector.numParticles, time);
}


// Destructor
Patch::~Patch()
{
}


// Generate Tecplot output
void Patch::generateOutput(std::string solutionName, vector2D data, int numParticles, double time)
{
	parametersList.logMessages("Generating Tecplot output", __FILE__, __LINE__);

	writeMeshTecplot(tecplotMesh, mesh);
	writeSolutionXY_T_Tecplot(solutionName, data, numParticles, time);
}


// Start the PIC loop within a Patch object
void Patch::startPIC()
{
	parametersList.logMessages("Starting PIC loop in patch " + std::to_string(patchID), __FILE__, __LINE__);

	for (int i = 0; i < parametersList.maximumNumberOfIterations; i++)
	{
		// TODO: Do the classes below really need to be defined as such, or can they
		// be replaced with functions of the Patch class? 

		ChargeProjector projector(&parametersList, &mesh, &particlesVector);
		
		// FDTD fdtd();

		FieldSolver solver(&parametersList, &mesh, &particlesVector);
		
		FieldInterpolator interpolator(&parametersList, &mesh, &particlesVector);

		ParticlePusher pusher(&parametersList, &mesh, &particlesVector, time);

		// MCC collisions();

		time += parametersList.timeStep;

		generateOutput(tecplotSolution, particlesVector.positionVector, particlesVector.numParticles, time);
	}
}