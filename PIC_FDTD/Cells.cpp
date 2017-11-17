//! \file
//! \brief Implementation of Cells class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#include "Cells.h"

// Default constructor
Cells::Cells()
{
}


// Constructor
Cells::Cells(CellBase baseCell)
{
	this->connectivity = baseCell.connectivity;
	this->geometry = baseCell.geometry;
}


// Destructor
Cells::~Cells()
{
}