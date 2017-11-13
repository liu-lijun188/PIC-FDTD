//! \file
//! \brief Definition of Ghost class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "GRID\cell.hpp"

//! \class Ghost
//! \brief Definition
class Ghost : public CellBase
{
public:
	Ghost();					//!< Default constructor
	Ghost(CellBase baseCell);	//!< Constructor
	~Ghost();					//!< Destructor
};