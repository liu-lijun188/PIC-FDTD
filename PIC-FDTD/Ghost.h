//! \file
//! \brief Definition of Ghost class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#pragma once

#include "GRID\cell.hpp"

//! \class Ghost
//! \brief Contains ghost cell properties, derived from CellBase
class Ghost : public CellBase
{
public:
	// Data members


	// Constructor/destructor
	Ghost();					//!< Default constructor
	Ghost(CellBase baseCell);	//!< Constructor
	~Ghost();					//!< Destructor


	// Methods

};