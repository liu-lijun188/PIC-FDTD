//! \file
//! \brief Definition of VectorCell class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Cells.h"

//! \class VectorCell
//! \brief Definition
class VectorCell
{
public:
	VectorCell();	//!< Default constructor
	~VectorCell();	//!< Destructor
	void allocate(std::vector<CellBase> cells);	//!< Allocate cells to cells attribute

	std::vector<Cells> cells;
};