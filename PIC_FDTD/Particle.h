//! \file
//! \brief Definition of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Parameters.h"
#include "CHEM\species.hpp"

using namespace std;

//! \class Particle
//! \brief Definition
class Particle : public species
{
public:
	Particle();									//!< Default constructor
	Particle(Parameters *localParametersList);	//!< Constructor
	~Particle();								//!< Destructor
};