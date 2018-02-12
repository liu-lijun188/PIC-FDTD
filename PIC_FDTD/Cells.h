//! \file
//! \brief Definition of Cells class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

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
	double width;						//!< Cell width
	double height;						//!< Cell height
	int leftCellID;						//!< ID of adjacent left cell
	int rightCellID;					//!< ID of adjacent right cell
	int topCellID;						//!< ID of adjacent top (up) cell
	int bottomCellID;					//!< ID of adjacent bottom (down) cell
	bool ghost;							//!< Check is cell is a ghost
	std::string firstNodePosition;		//!< Position of first node
	std::vector<int> listOfParticles;	//!< List of particles in the cell


	// Constructor/destructor
	Cells();							//!< Default constructor
	Cells(CellBase baseCell);			//!< Constructor
	~Cells();							//!< Destructor


	// Methods
	int minimumID();					//!< Find minimum adjacent ID

};