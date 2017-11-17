//! \file
//! \brief Definition of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#pragma once

#include "Parameters.h"
#include "Mesh.h"
#include "CHEM\species.hpp"

//! \class Particle
//! \brief Contains all particle data, derived from species class
class Particle : public species
{
public:
	// Data members
	int particleID;										//!< Particle ID
	int cellID;											//!< Current cell ID
	std::vector<double> position;						//!< Particle position vector
	std::vector<double> velocity;						//!< Particle velocity vector


	// Constructor/destructor
	Particle();											//!< Default constructor
	Particle(Parameters *parametersList, Mesh *mesh, 
		int patchID, int cellID, int particleID);		//!< Constructor
	~Particle();										//!< Destructor


	// Methods

};