//! \file
//! \brief Definition of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#pragma once

#include <random>

#include "Parameters.h"
#include "Mesh.h"
#include "CHEM\species.hpp"

//! \class Particle
//! \brief Contains all particle data, derived from species class
class Particle : public species
{
public:
	// Data members
	int particleID;							//!< Particle ID
	int cellID;								//!< Current cell ID
	std::vector<double> position;			//!< Particle position vector
	std::vector<double> velocity;			//!< Particle velocity vector

	std::vector<double> fields
		{ -1.0, -1.0, -1.0, -1.0 }; 		//!< Electromagnetic fields (Ex, Ey, Bx, By)
	std::vector<double> lorentz	
		{ -1.0,-1.0 };						//!< Lorentz force (Fx, Fy)

	// Constructor/destructor
	Particle();								//!< Default constructor
	Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, 
		int particleID, int index);			//!< Constructor
	~Particle();							//!< Destructor


	// Methods

};