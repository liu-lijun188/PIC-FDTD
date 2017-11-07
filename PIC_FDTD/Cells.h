//! \file
//! \brief Definition of Cells class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "GRID\cell.hpp"

//! \class Cells
//! \brief Definition
class Cells : public CellBase
{
public:
	Cells();					//!< Default constructor
	Cells(CellBase baseCell);	//!< Constructor
	~Cells();					//!< Destructor
};