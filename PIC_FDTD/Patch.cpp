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

	writeMeshTecplot(tecplotMesh, mesh);

	generateParticleOutput(particlesVector.plotVector, particlesVector.numParticles, time);
	generateNodeOutput(mesh, time);
}


// Destructor
Patch::~Patch()
{
}


// Generate Tecplot output
void Patch::generateParticleOutput(vector2D data, int numParticles, double time)
{
	parametersList.logMessages("Generating Tecplot particle output", __FILE__, __LINE__);
	
	// Plot style can be T (plot all particles at each time step), TA (animated),
	// NT (plot each particle over all time steps) and NTA (animated)  
	writeSolutionXY_NTA_Tecplot(tecplotParticleSolution, data, numParticles, time);
}

void Patch::generateNodeOutput(Mesh mesh, double time)
{
	parametersList.logMessages("Generating Tecplot node output", __FILE__, __LINE__);

	writeSolutionNodeTecplot(tecplotNodeSolution, mesh, time);
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

		// Generate plots only at intervals
		if (static_cast<int>(time / parametersList.timeStep) % 3 == 0)
		{
			generateParticleOutput(particlesVector.plotVector, particlesVector.numParticles, time);
			generateNodeOutput(mesh, time);
		}
	}
}