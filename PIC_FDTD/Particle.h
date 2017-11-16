//! \file
//! \brief Definition of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Parameters.h"
#include "Mesh.h"
#include "CHEM\species.hpp"

//! \class Particle
//! \brief Definition
class Particle : public species
{
public:
	Particle();									//!< Default constructor
	Particle(Parameters *parametersList, Mesh *mesh, int patchID,
		int cellID, int particleID);			//!< Constructor
	~Particle();								//!< Destructor

	int particleID;
	int cellID;
	std::vector<double> position;
	std::vector<double> velocity;
};