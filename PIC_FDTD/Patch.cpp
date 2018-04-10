//! \file
//! \brief Implementation of Patch class 
//! \author Rahul Kalampattel
//! \date Last updated April 2018

#include "Patch.h"

// Default constructor
Patch::Patch()
{
}


// Constructor
Patch::Patch(Parameters *parametersList, int patchID)
{
	parametersList->logMessages("Initialising patch " + std::to_string(patchID), __FILENAME__, __LINE__, 1);

	time = 0;
	this->patchID = patchID;
	this->parametersList = *parametersList;

	mesh = Mesh(&this->parametersList, "PIC");
	particlesVector = VectorParticle(&this->parametersList, &mesh, patchID);

	parametersList->logBrief("Initialising Tecplot output files", 1);
	writeMeshTecplot(parametersList->tecplotMesh, mesh);

	generateParticleOutput(particlesVector.plotVector, particlesVector.numParticles, time);
	generateNodeOutput(mesh, time);
	generateGlobalOutput(0.0, 0.0, time);
}


// Destructor
Patch::~Patch()
{
}


// Generate Tecplot output
void Patch::generateParticleOutput(vector2D data, int numParticles, double time)
{
	// Plot style can be T (plot all particles at each time step), TA (animated),
	// NT (plot each particle over all time steps) and NTA (animated)  
	writeSolutionXY_NTA_Tecplot(parametersList.tecplotParticleSolution, data, numParticles, time);
}

void Patch::generateNodeOutput(Mesh mesh, double time)
{
	writeSolutionNodeTecplot(parametersList.tecplotNodeSolution, mesh, time);
}

void Patch::generateGlobalOutput(double EK, double EP, double time)
{
	writeSolution_T_Tecplot(parametersList.tecplotGlobalSolution, EK, EP, 
		parametersList.maximumNumberOfIterations / parametersList.plotFrequency, time);
}

// Start the PIC loop within a Patch object
void Patch::startPIC()
{
	numErrors = parametersList.numErrors;
	if (numErrors == 0)
	{
		parametersList.logMessages("Starting PIC loop in patch " + std::to_string(patchID), __FILENAME__, __LINE__, 1);

		for (int i = 0; i < parametersList.maximumNumberOfIterations; i++)
		{
			parametersList.logMessages("Starting iteration " + std::to_string(i + 1),
				__FILENAME__, __LINE__, 1);

			// TODO: Do the classes below really need to be defined as such, or can they
			// be replaced with functions of the Patch class? 

			ChargeProjector projector(&parametersList, &mesh, &particlesVector);

			if (static_cast<int>(time / parametersList.timeStep) % parametersList.FDTDfrequency == 0)
			{
				// FDTD fdtd(&parametersList, &mesh);
			}

			FieldSolver solver(&parametersList, &mesh);

			FieldInterpolator interpolator(&parametersList, &mesh, &particlesVector);

			ParticlePusher pusher(&parametersList, &mesh, &particlesVector, time);

			if (static_cast<int>(time / parametersList.timeStep) % parametersList.MCCfrequency == 0)
			{
				// MCC collisions(&parametersList, &mesh, &particlesVector);
			}

			// TODO: At certain intervals, calculate the Debye length, plasma frequency, 
			// etc. in order to check that initial assumptions and methods used
			// are still valid, e.g. is spatial grid still fine enough to resolve
			// Debye length? Stability of leapfrog method and field solver??

			numErrors = parametersList.numErrors;
			if (numErrors != 0)
			{
				break;
			}

			time += parametersList.timeStep;

			// Generate plots at specified intervals
			if (static_cast<int>(time / parametersList.timeStep) % parametersList.plotFrequency == 0)
			{
				double EK = particlesVector.calculateEK();
				double EP = mesh.nodesVector.calculateEP();

				generateParticleOutput(particlesVector.plotVector, particlesVector.numParticles, time);
				generateNodeOutput(mesh, time);
				generateGlobalOutput(EK, EP, time);
				parametersList.logBrief("Tecplot output generated", 1);
			}
		}
	}
}