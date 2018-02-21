//! \file
//! \brief Implementation of ParticlePusher class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#include "ParticlePusher.h"

// Default constructor
ParticlePusher::ParticlePusher()
{
}

// Constructor
ParticlePusher::ParticlePusher(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector)
{
	// TODO: Incorporate Boris methods to handle B field rotation

	// TODO: Leapfrog method 
	// If t==0, shift velocity back by half a time step, i.e. v += E*q*(0.5*dt/m), 
	// where E*q is Lorentz force, dividing by m gives acceleration, 
	// multiplying by dt gives velocity, and the 0.5 allows a half step shift.
	// Then, for all time steps including t==0, v += E*q*(dt/m), and x += v*dt
	// Remember to shift v forwards half a time step when plotting!!!

	// Currently enforced BCs: fixed (sticky) walls in y direction, periodic in x

	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// Update x position
		particlesVector->particleVector[i].position[0] += 
			parametersList->timeStep * particlesVector->particleVector[i].velocity[0]; 

		double displacementL = particlesVector->particleVector[i].position[0] - 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].left;
		double displacementR = particlesVector->particleVector[i].position[0] -
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right;

		// Update cell ID in x direction, exiting left
		if (displacementL < 0.0)
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);

			// Particle remains inside domain
			if (mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].leftCellID > 0)
			{	
				particlesVector->particleVector[i].cellID =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].leftCellID;
			}
			// Particle crosses left boundary
			else
			{	
				particlesVector->particleVector[i].cellID =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicXCellID;

				// Shift x position
				particlesVector->particleVector[i].position[0] = displacementL +
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right;
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update cell ID in x direction, exiting right
		else if (displacementR > 0.0)
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);

			// Particle remains inside domain
			if (mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].rightCellID > 0)
			{
				particlesVector->particleVector[i].cellID =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].rightCellID;
			}
			// Particle crosses right boundary
			else
			{
				particlesVector->particleVector[i].cellID =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicXCellID;

				// Shift x position
				particlesVector->particleVector[i].position[0] = displacementR +
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].left;
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update y position
		particlesVector->particleVector[i].position[1] +=
			parametersList->timeStep * particlesVector->particleVector[i].velocity[1];

		double displacementB = particlesVector->particleVector[i].position[1] -
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;
		double displacementT = particlesVector->particleVector[i].position[1] -
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;

		// Update cell ID in y direction, exiting bottom
		if (displacementB < 0.0)
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
			
			// Particle remains inside domain
			if (mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottomCellID > 0)
			{
				particlesVector->particleVector[i].cellID =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottomCellID;
			}
			// Particle crosses bottom boundary
			else
			{
				// Stick particle to boundary
				particlesVector->particleVector[i].position[1] =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update cell ID in y direction, exiting top
		else if (displacementT > 0.0)
		{
			mesh->removeParticlesFromCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
			
			// Particle remains inside domain
			if (mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].topCellID > 0)
			{
				particlesVector->particleVector[i].cellID =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].topCellID;
			}
			// Particle crosses top boundary
			else
			{
				// Stick particle to boundary
				particlesVector->particleVector[i].position[1] =
					mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		particlesVector->updatePositionVector(&particlesVector->particleVector[i]);
	}
}


// Destructor
ParticlePusher::~ParticlePusher()
{
}