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
MCC::MCC(Parameters *parametersList, VectorParticle *particlesVector)
{
	// TODO: Check that it is appropriate to use MCC (compare particle densities,
	// collision frequencies, etc.)

	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// TODO: Calculate collision probability, P = 1 - exp(-n_n*sigma*g*dt),
		// where n_n is the density of the target gas at the particle location,
		// sigma is the collision cross section (determined from tabulated data),
		// g is the relative velocity between species, and dt is the time step
		// for calculating collisions (usually larger than simulation time step).
		// If probability is greater than a random number, then collision occurs.

		// TODO: Process specific collision handler, e.g. for CEX collisions, replace
		// velocities of the collided particle with values from a Maxwellian distribution.
		// Specific method depends on the types of collisions being modelled, e.g.
		// charge exchange, momentum exchange, ionisation, etc. 
	}
}


// Destructor
MCC::~MCC()
{
}