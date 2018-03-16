//! \file
//! \brief Implementation of ParticlePusher class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "ParticlePusher.h"

// Default constructor
ParticlePusher::ParticlePusher()
{
}

// Constructor
ParticlePusher::ParticlePusher(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector, double time)
{
	// TODO: Consider working with normalised equations (e.g. x/h, t/timeStep, etc.)
	// to reduce number of computations at each stage

	// TODO: Check that time step is fine enough for pusher stability
	// Leapfrog method - remember to shift v forwards 0.5 time steps when plotting!
	if (time == 0.0)
	{
		for (int i = 0; i < particlesVector->numParticles; i++)
		{
			double vXInitial = particlesVector->particleVector[i].velocity[0];

			particlesVector->particleVector[i].velocity[0] -=
				particlesVector->particleVector[i].basic.q * 
				(particlesVector->particleVector[i].fields[0] +
					particlesVector->particleVector[i].fields[2] * 
					particlesVector->particleVector[i].velocity[1]) * 0.5 *
				parametersList->timeStep / particlesVector->particleVector[i].basic.m;
		
			particlesVector->particleVector[i].velocity[1] -=
				particlesVector->particleVector[i].basic.q *
				(particlesVector->particleVector[i].fields[1] -
					particlesVector->particleVector[i].fields[2] *
					vXInitial) * 0.5 * parametersList->timeStep / 
				particlesVector->particleVector[i].basic.m;
		}
	}

	// TODO: Implement open boundaries, where particles leave the domain and are
	// removed from the global particles list, with new particles injected (from
	// the opposite side??) if charge balance is required

	// TODO: At the moment both Dirichlet and Neumann BCs cause reflection, however
	// in waves, Dirichlet causes a sign change while Neumann does not (perfect 
	// reflection) - check whether this is also correct for particle simulation

	// Currently available BCs: periodic, Dirichlet and Neumann
	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// Update velocity using Boris method:
		// 1. Half acceleration
		double vXMinus = particlesVector->particleVector[i].velocity[0] + 0.5 *
			particlesVector->particleVector[i].basic.q * parametersList->timeStep * 
			particlesVector->particleVector[i].fields[0] / particlesVector->particleVector[i].basic.m;
		double vYMinus = particlesVector->particleVector[i].velocity[1] + 0.5 *
			particlesVector->particleVector[i].basic.q * parametersList->timeStep *
			particlesVector->particleVector[i].fields[1] / particlesVector->particleVector[i].basic.m;

		// 2. Rotation
		double tVector = particlesVector->particleVector[i].basic.q * 0.5 *
			parametersList->timeStep * particlesVector->particleVector[i].fields[2] /
			particlesVector->particleVector[i].basic.m;
		double sVector = 2 * tVector / (1 + tVector * tVector);

		double vXDashed = vXMinus + vYMinus * tVector;
		double vYDashed = vYMinus - vXMinus * tVector;

		double vXPlus = vXMinus + vYDashed * sVector;
		double vYPlus = vYMinus - vXDashed * sVector;

		// 3. Half acceleration
		particlesVector->particleVector[i].velocity[0] = vXPlus + 0.5 *
			particlesVector->particleVector[i].basic.q * parametersList->timeStep *
			particlesVector->particleVector[i].fields[0] / particlesVector->particleVector[i].basic.m;

		particlesVector->particleVector[i].velocity[1] = vYPlus + 0.5 *
			particlesVector->particleVector[i].basic.q * parametersList->timeStep *
			particlesVector->particleVector[i].fields[1] / particlesVector->particleVector[i].basic.m;

		// Update x position
		particlesVector->particleVector[i].position[0] += parametersList->timeStep * 
			particlesVector->particleVector[i].velocity[0]; 

		double displacementL = particlesVector->particleVector[i].position[0] - 
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].left;
		double displacementR = particlesVector->particleVector[i].position[0] -
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right;

		if ((displacementL < 0.0 && abs(displacementL) >= mesh->h) || (displacementR > 0.0 && abs(displacementR) >= mesh->h))
		{
			parametersList->logBrief("Particle " + std::to_string(i + 1) + " has moved more than one cell length", 3);
			break;
		}

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
			// Particle crosses left boundary of domain
			else
			{
				if (parametersList->xBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicXCellID;

					// Shift x position
					particlesVector->particleVector[i].position[0] = displacementL +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right;
				}
				else if (parametersList->xBCType == "dirichlet" || 
						 parametersList->xBCType == "neumann")
				{
					// Reflect particle from boundary
					particlesVector->particleVector[i].position[0] = -displacementL +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].left;

					// Reverse x velocity
					particlesVector->particleVector[i].velocity[0] *= -1.0;
				}

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
				if (parametersList->xBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicXCellID;

					// Shift x position
					particlesVector->particleVector[i].position[0] = displacementR +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].left;
				}
				else if (parametersList->xBCType == "dirichlet" || 
						 parametersList->xBCType == "neumann")
				{
					// Reflect particle from boundary
					particlesVector->particleVector[i].position[0] = -displacementR +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right;

					// Reverse x velocity
					particlesVector->particleVector[i].velocity[0] *= -1.0;
				}
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update y position
		particlesVector->particleVector[i].position[1] += parametersList->timeStep * 
			particlesVector->particleVector[i].velocity[1];

		double displacementB = particlesVector->particleVector[i].position[1] -
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;
		double displacementT = particlesVector->particleVector[i].position[1] -
			mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;

		if ((displacementB < 0.0 && abs(displacementB) >= mesh->h) || (displacementT > 0.0 && abs(displacementT) >= mesh->h))
		{
			parametersList->logBrief("Particle " + std::to_string(i + 1) + " has moved more than one cell length", 3);
			break;
		}

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
				if (parametersList->yBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicYCellID;

					// Shift y position
					particlesVector->particleVector[i].position[0] = displacementB +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;
				}
				else if (parametersList->yBCType == "dirichlet" || 
						 parametersList->yBCType == "neumann")
				{
					// Reflect particle from boundary
					particlesVector->particleVector[i].position[1] = -displacementB +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;

					// Reverse y velocity
					particlesVector->particleVector[i].velocity[1] *= -1.0;
				}
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
				if (parametersList->yBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicYCellID;

					// Shift y position
					particlesVector->particleVector[i].position[0] = displacementT +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;
				}
				else if (parametersList->yBCType == "dirichlet" ||
						 parametersList->yBCType == "neumann")
				{
					// Reflect particle from boundary
					particlesVector->particleVector[i].position[1] = -displacementT +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;

					// Reverse y velocity
					particlesVector->particleVector[i].velocity[1] *= -1.0;
				}
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		particlesVector->updatePlotVector(&particlesVector->particleVector[i]);
	}

	// TODO: Shift v forwards half a time step to sync v and x for plotting

	// TODO: Calculate kinetic energy of particle and record (or do this later 
	// when plotting), similarly for potential energy

	parametersList->logBrief("Particle pusher exited", 1);
}


// Destructor
ParticlePusher::~ParticlePusher()
{
}