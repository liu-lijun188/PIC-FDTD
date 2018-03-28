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

	// Leapfrog method
	if (time == 0.0)
	{
		for (int i = 0; i < particlesVector->numParticles; i++)
		{
			double v1Initial = particlesVector->particleVector[i].velocity[0];
			double v2Initial = particlesVector->particleVector[i].velocity[1];

			particlesVector->particleVector[i].velocity[0] -=
				particlesVector->particleVector[i].basic.q * 
				(particlesVector->particleVector[i].EMfield[0] +
					particlesVector->particleVector[i].EMfield[5] * 
					particlesVector->particleVector[i].velocity[1] - 
					particlesVector->particleVector[i].EMfield[4] *
					particlesVector->particleVector[i].velocity[2]) * 0.5 *
				parametersList->timeStep / particlesVector->particleVector[i].basic.m;
		
			particlesVector->particleVector[i].velocity[1] -=
				particlesVector->particleVector[i].basic.q *
				(particlesVector->particleVector[i].EMfield[1] +
					particlesVector->particleVector[i].EMfield[3] *
					particlesVector->particleVector[i].velocity[2] -
					particlesVector->particleVector[i].EMfield[5] * v1Initial) * 0.5 *
				parametersList->timeStep / particlesVector->particleVector[i].basic.m;

			particlesVector->particleVector[i].velocity[2] -=
				particlesVector->particleVector[i].basic.q *
				(particlesVector->particleVector[i].EMfield[2] +
					particlesVector->particleVector[i].EMfield[4] * v1Initial -
					particlesVector->particleVector[i].EMfield[3] * v2Initial) * 0.5 *
				parametersList->timeStep / particlesVector->particleVector[i].basic.m;
		}
	}

	// TODO: Inject new particles to maintain charge balance with open BCs

	// TODO: At the moment both Dirichlet and Neumann BCs cause reflection, however
	// in waves, Dirichlet causes a sign change while Neumann does not (perfect 
	// reflection) - check whether this is also correct for particle simulation
	
	// Currently available BCs: periodic, open, Dirichlet and Neumann
	for (int i = 0; i < particlesVector->numParticles; i++)
	{		
		// Update velocity using Boris method:
		double vMinus[3];
		double tVector[3], sVector[3];
		for (int j = 0; j < 3; j++)
		{
			// 1. Half acceleration
			vMinus[j] = particlesVector->particleVector[i].velocity[j] + 0.5 *
				particlesVector->particleVector[i].basic.q * parametersList->timeStep *
				particlesVector->particleVector[i].EMfield[j] / particlesVector->particleVector[i].basic.m;

			// 2. Rotation
			double theta = 2.0 * abs(atan(0.5 * particlesVector->particleVector[i].EMfield[j+3] *
				parametersList->timeStep * particlesVector->particleVector[i].basic.q /
				particlesVector->particleVector[i].basic.m)) * 180.0 / std::_Pi;

			if (theta > 45.0)
			{
				parametersList->logBrief("Rotation angle has exceeded 45 degrees", 3);
				break;
			}

			tVector[j] = particlesVector->particleVector[i].basic.q * 0.5 *
				parametersList->timeStep * particlesVector->particleVector[i].EMfield[j+3] /
				particlesVector->particleVector[i].basic.m;
			sVector[j] = 2 * tVector[j] / (1 + tVector[j] * tVector[j]);
		}

		double v1Dashed = vMinus[0] + vMinus[1] * tVector[2] - vMinus[2] * tVector[1];
		double v2Dashed = vMinus[1] - vMinus[0] * tVector[2] + vMinus[2] * tVector[0];
		double v3Dashed = vMinus[2] + vMinus[0] * tVector[1] - vMinus[1] * tVector[0];

		double v1Plus = vMinus[0] + v2Dashed * sVector[2] - v3Dashed * sVector[1];
		double v2Plus = vMinus[1] - v1Dashed * sVector[2] + v3Dashed * sVector[0];
		double v3Plus = vMinus[2] + v1Dashed * sVector[1] - v2Dashed * sVector[0];

		// 3. Half acceleration
		particlesVector->particleVector[i].velocity[0] = v1Plus + 0.5 *
			particlesVector->particleVector[i].basic.q * parametersList->timeStep *
			particlesVector->particleVector[i].EMfield[0] / particlesVector->particleVector[i].basic.m;

		particlesVector->particleVector[i].velocity[1] = v2Plus + 0.5 *
			particlesVector->particleVector[i].basic.q * parametersList->timeStep *
			particlesVector->particleVector[i].EMfield[1] / particlesVector->particleVector[i].basic.m;

		particlesVector->particleVector[i].velocity[2] = v3Plus + 0.5 *
			particlesVector->particleVector[i].basic.q * parametersList->timeStep *
			particlesVector->particleVector[i].EMfield[2] / particlesVector->particleVector[i].basic.m;

		// TODO: Does third velocity component need to be included in Courant 
		// number calculation since only 2 spatial dimensions are being modelled?
		double courantNumber = (particlesVector->particleVector[i].velocity[0] +
			particlesVector->particleVector[i].velocity[1] + 
			particlesVector->particleVector[i].velocity[2]) * parametersList->timeStep /
			mesh->h;

		if (courantNumber > 1.0)
		{
			parametersList->logBrief("CFL condition exceeded, consider adjusting time step", 2);
			if (courantNumber > 1.5)
			{
				parametersList->logBrief("CFL condition exceeded 1.5, stopping pusher", 3);
				break;
			}
		}

		// Update Cartesian x/cylindrical z position
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

		// Update cell ID in Cartesian x/cylindrical z direction, exiting left
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
				if (parametersList->leftBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicX1CellID;

					// Shift Cartesian x/ cylindrical z position
					particlesVector->particleVector[i].position[0] = displacementL +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right;
				}
				else if (parametersList->leftBCType == "open")
				{
					particlesVector->removeParticleFromSim(particlesVector->particleVector[i].particleID);
					i -= 1;
					continue;
				}
				else if (parametersList->leftBCType == "dirichlet" ||
						 parametersList->leftBCType == "neumann")
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

		// Update cell ID in Cartesian x/ cylindrical z direction, exiting right
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
				if (parametersList->rightBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicX1CellID;

					// Shift Cartesian x/ cylindrical z position
					particlesVector->particleVector[i].position[0] = displacementR +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].left;
				}
				else if (parametersList->rightBCType == "open")
				{
					particlesVector->removeParticleFromSim(particlesVector->particleVector[i].particleID);
					i -= 1;
					continue;
				}
				else if (parametersList->rightBCType == "dirichlet" ||
						 parametersList->rightBCType == "neumann")
				{
					// Reflect particle from boundary
					particlesVector->particleVector[i].position[0] = -displacementR +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].right;

					// Reverse Cartesian x/ cylindrical z velocity
					particlesVector->particleVector[i].velocity[0] *= -1.0;
				}
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update Cartesian y/ cylindrical r position
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

		// Update cell ID in Cartesian y/ cylindrical r direction, exiting bottom
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
				// TODO: Doesn't make sense to have periodic bottom BC for cylindrical case
				if (parametersList->bottomBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicX2CellID;

					// Shift Cartesian y/ cylindrical r position
					particlesVector->particleVector[i].position[1] = displacementB +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;
				}
				else if (parametersList->bottomBCType == "open")
				{
					particlesVector->removeParticleFromSim(particlesVector->particleVector[i].particleID);
					i -= 1;
					continue;
				}
				else if (parametersList->bottomBCType == "dirichlet" ||
						 parametersList->bottomBCType == "neumann")
				{
					// Reflect particle from boundary
					particlesVector->particleVector[i].position[1] = -displacementB +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;

					// Reverse Cartesian y/ cylindrical r velocity
					particlesVector->particleVector[i].velocity[1] *= -1.0;
				}
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update cell ID in Cartesian y/ cylindrical r direction, exiting top
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
				// TODO: Doesn't make sense to have periodic top BC for cylindrical case
				if (parametersList->topBCType == "periodic")
				{
					particlesVector->particleVector[i].cellID =
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicX2CellID;

					// Shift Cartesian y/ cylindrical r position
					particlesVector->particleVector[i].position[1] = displacementT +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;
				}
				else if (parametersList->topBCType == "open")
				{
					particlesVector->removeParticleFromSim(particlesVector->particleVector[i].particleID);
					i -= 1;
					continue;
				}
				else if (parametersList->topBCType == "dirichlet" ||
						 parametersList->topBCType == "neumann")
				{
					// Reflect particle from boundary
					particlesVector->particleVector[i].position[1] = -displacementT +
						mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;

					// Reverse Cartesian y/ cylindrical r velocity
					particlesVector->particleVector[i].velocity[1] *= -1.0;
				}
			}

			mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
				particlesVector->particleVector[i].particleID);
		}

		// Update cylindrical theta position (no need to update Cartesian z)
		if (parametersList->axisymmetric)
		{
			particlesVector->particleVector[i].position[2] += parametersList->timeStep *
				particlesVector->particleVector[i].velocity[2];

			// TODO: Check that new position does not exceed height of simulation domain
			double newX2 = particlesVector->particleVector[i].velocityMagnitude();

			// TODO: Check that rotation angle is reasonable
			double rotation = atan(abs(particlesVector->particleVector[i].position[2]) /
				particlesVector->particleVector[i].position[1]);

			displacementT += newX2 - particlesVector->particleVector[i].position[1];
			if (displacementT > 0.0 && abs(displacementT) >= mesh->h)
			{
				parametersList->logBrief("Particle " + std::to_string(i + 1) + " has moved more than one cell length", 3);
				break;
			}

			// Update r and theta positions
			particlesVector->particleVector[i].position[1] = newX2;
			particlesVector->particleVector[i].position[2] = 0.0;

			// Rotate velocities back to z-r plane
			double velocity2 = particlesVector->particleVector[i].velocity[1];
			particlesVector->particleVector[i].velocity[1] = cos(rotation) *
				particlesVector->particleVector[i].velocity[1] - sin(rotation) *
				particlesVector->particleVector[i].velocity[2];
			particlesVector->particleVector[i].velocity[2] = sin(rotation) *
				velocity2 + cos(rotation) *	particlesVector->particleVector[i].velocity[2];

			// Update cell ID in Cartesian y/ cylindrical r direction, exiting top
			if (displacementT > 0.0)
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
					// TODO: Doesn't make sense to have periodic top BC for cylindrical case
					if (parametersList->topBCType == "periodic")
					{
						particlesVector->particleVector[i].cellID =
							mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].periodicX2CellID;

						// Shift Cartesian y/ cylindrical r position
						particlesVector->particleVector[i].position[1] = displacementT +
							mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].bottom;
					}
					else if (parametersList->topBCType == "open")
					{
						particlesVector->removeParticleFromSim(particlesVector->particleVector[i].particleID);
						i -= 1;
						continue;
					}
					else if (parametersList->topBCType == "dirichlet" ||
						parametersList->topBCType == "neumann")
					{
						// Reflect particle from boundary
						particlesVector->particleVector[i].position[1] = -displacementT +
							mesh->cellsVector.cells[particlesVector->particleVector[i].cellID - 1].top;

						// Reverse Cartesian y/ cylindrical r velocity
						particlesVector->particleVector[i].velocity[1] *= -1.0;
					}
				}

				mesh->addParticlesToCell(particlesVector->particleVector[i].cellID,
					particlesVector->particleVector[i].particleID);
			}
		}
		particlesVector->updatePlotVector(&particlesVector->particleVector[i]);
	}

	// TODO: Shift v forwards half a time step to sync v and x for plotting

	parametersList->logBrief("Particle pusher exited", 1);
}


// Destructor
ParticlePusher::~ParticlePusher()
{
}