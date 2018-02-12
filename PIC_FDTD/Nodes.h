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
	double charge = 0;			//!< Charge at the grid node
	bool internal;				//!< Check if node is internal

	// Constructor/destructor
	Nodes();					//!< Default constructor
	Nodes(NodeBase baseNode);	//!< Constructor
	~Nodes();					//!< Destructor

	// Methods

};