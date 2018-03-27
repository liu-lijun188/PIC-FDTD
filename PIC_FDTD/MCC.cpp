//! \file
//! \brief Implementation of MCC class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "MCC.h"

// Default constructor
MCC::MCC()
{
}


// Constructor
MCC::MCC(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector)
{
	// TODO: Check that it is appropriate to use MCC (compare particle densities,
	// collision frequencies, etc.)

	// particlesVector->addParticleToSim(parametersList, mesh, 1, "electron");

	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// particlesVector->removeParticleFromSim(particlesVector->particleVector[i].particleID);
		// break;

		// TODO: Calculate collision probability, P = 1 - exp(-n_n*sigma*g*dt),
		// where n_n is the density of the target gas at the particle location,
		// sigma is the collision cross section (determined from tabulated data),
		// g is the relative velocity between species, and dt is the time step
		// for calculating collisions (usually larger than simulation time step).
		// If probability is greater than a random number, then collision occurs.

		// double sigma = (-0.8821 * log(g) + 15.1262)

		// TODO: Process specific collision handler, e.g. for CEX collisions, replace
		// velocities of the collided particle with values from a Maxwellian distribution.
		// 
		// Types of collisions include:
		// Ionisation:		  Xe   + e-	   -> Xe+   + 2e-
		// Recombination:	  Xe+  + e-	   -> Xe
		// Charge exchange:	  Xe_f + Xe+_s -> Xe+_f + Xe_s
		// Momentum exchange: Xe_f + Xe_s  -> Xe_s  + Xe_f (not well supported by MCC?)
		//
		// Collisions modelled depends on simulation type:
		// electron: ionisation (+1 electron), recombination (-1 electron)
		// partial: ionisation (-1 neutral, +1 ion), recombination (+1 neutral, -1 ion), charge exchange
		// full: ionisation (-1 neutral, +1 ion/electron), recombination (+1 neutral, -1 ion/electron), charge exchange
		//
		// Additionally, particle production occurs as a result of inductive or
		// electron heating (RF thruster)
	}
}


// Destructor
MCC::~MCC()
{
}