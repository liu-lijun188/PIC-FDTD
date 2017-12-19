//! \file
//! \brief Definition of Nodes class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#pragma once

#include "GRID\node.hpp"

//! \class Nodes
//! \brief Contains node properties, derived from NodeBase
class Nodes : public NodeBase
{
public:
	// Data members
	double charge = 0;			//!< Charge at the grid node

	// Constructor/destructor
	Nodes();					//!< Default constructor
	Nodes(NodeBase baseNode);	//!< Constructor
	~Nodes();					//!< Destructor

	// Methods

};