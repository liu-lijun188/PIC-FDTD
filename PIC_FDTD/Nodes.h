//! \file
//! \brief Definition of Nodes class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#pragma once

#include "GRID\node.hpp"

//! \class Nodes
//! \brief Contains node properties, derived from NodeBase
class Nodes : public NodeBase
{
public:
	// Data members
	int leftNodeID = -1;		//!< ID of node to left
	int rightNodeID = -1;		//!< ID of node to right
	int topNodeID = -1;			//!< ID of node to top
	int bottomNodeID = -1;		//!< ID of node to bottom
	std::string boundaryType;	//!< Position on boundary (internal if FALSE)

	double charge = -1;			//!< Charge at the grid node
	double rho = -1;			//!< Charge density at the grid node
	double phi = -1;			//!< Potential at the grid node

	std::vector<double> fields
	{ 0.0, 0.0, 0.0, 0.0 };	//!< Electromagnetic fields (Ex, Ey, Bx, By)
	
	// Constructor/destructor
	Nodes();					//!< Default constructor
	Nodes(NodeBase baseNode);	//!< Constructor
	~Nodes();					//!< Destructor


	// Methods

};