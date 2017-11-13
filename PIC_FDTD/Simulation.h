//! \file
//! \brief Definition of Simulation class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Parameters.h"
#include "VectorPatch.h"

//! \class Simulation
//! \brief Definition
class Simulation
{
public: 
	Simulation();							//!< Default constructor
	Simulation(Parameters *parametersList);	//!< Constructor
	~Simulation();							//!< Destructor
	void loadBalance();						//!< Perform load balancing across patches
};