//! \file
//! \brief Definition of VectorGhost class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#pragma once

#include "Ghost.h"

//! \class VectorGhost
//! \brief Create and manage a vector of Ghost objects
class VectorGhost
{
public:
	// Data members
	std::vector<Ghost> ghosts;					//!< Vector of Ghost objects


	// Constructor/destructor
	VectorGhost();								//!< Default constructor
	~VectorGhost();								//!< Destructor


	// Methods
	void allocate(std::vector<CellBase> cells);	//!< Allocate CellBase elements to ghosts data member
};