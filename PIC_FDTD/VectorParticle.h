//! \file
//! \brief Definition of VectorParticle class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#pragma once

#include "Particle.h"

//! \class VectorParticle
//! \brief Create and manage a vector of Particle objects
class VectorParticle
{
public:
	// Data members
	std::vector<Particle> particleVector;			//!< Vector of Particle objects
	int numParticles;								//!< Size of particleVector								
	vector2D positionVector;						//!< Store particle position, cell ID and particle ID for plotting


	// Constructor/destructor
	VectorParticle();								//!< Default constructor
	VectorParticle(Parameters *parametersList,
		Mesh *mesh, int patchID);					//!< Constructor
	~VectorParticle();								//!< Destructor


	// Methods
	void updatePositionVector(Particle *particle);	//!< Update state of positionVector
};