//! \file
//! \brief Definition of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Parameters.h"
#include "CHEM\species.hpp"

//! \class Particle
//! \brief Definition
class Particle : public species
{
public:
	Particle();									//!< Default constructor
	Particle(Parameters *parametersList, int patchID, 
		int cellID, int particleID);			//!< Constructor
	~Particle();								//!< Destructor

	std::vector<double> position;
};