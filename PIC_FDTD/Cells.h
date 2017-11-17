//! \file
//! \brief Definition of Cells class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#pragma once

#include "GRID\cell.hpp"

//! \class Cells
//! \brief Contains cell properties, derived from CellBase
class Cells : public CellBase
{
public:
	// Data members
	double left;						//!< Left cell boundary
	double right;						//!< Right cell boundary
	double top;							//!< Top (up) cell boundary
	double bottom;						//!< Bottom (down) cell boundary
	int leftCellID;						//!< ID of adjacent left cell
	int rightCellID;					//!< ID of adjacent right cell
	int topCellID;						//!< ID of adjacent top (up) cell
	int bottomCellID;					//!< ID of adjacent bottom (down) cell
	std::vector<int> listOfParticles;	//!< List of particles in the cell


	// Constructor/destructor
	Cells();							//!< Default constructor
	Cells(CellBase baseCell);			//!< Constructor
	~Cells();							//!< Destructor


	// Methods

};