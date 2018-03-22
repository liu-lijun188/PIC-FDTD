//! \file
//! \brief Definition of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

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
	int particleID;							//!< Particle ID
	int cellID;								//!< Current cell ID
	std::vector<double> position;			//!< Particle position vector
	std::vector<double> velocity;			//!< Particle velocity vector

	std::vector<double> Efield
		{ -1.0, -1.0, -1.0 };		 		//!< Electric field
	std::vector<double> Bfield
		{ -1.0, -1.0, -1.0 };	 			//!< Magnetic field


	// Constructor/destructor
	Particle();								//!< Default constructor
	Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, 
		int particleID, int index);			//!< Initial constructor
	Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID,
		int particleID, std::string type);	// Single particle constructor
	~Particle();							//!< Destructor


	// Methods

};