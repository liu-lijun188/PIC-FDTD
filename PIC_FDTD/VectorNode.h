//! \file
//! \brief Definition of VectorNode class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#pragma once

#include "Nodes.h"

//! \class VectorNode
//! \brief Create and manage a vector of Nodes objects
class VectorNode
{
public:
	// Data members
	std::vector<Nodes> nodes;					//!< Vector of Nodes objects


	// Constructor/destructor
	VectorNode();								//!< Default constructor
	~VectorNode();								//!< Destructor


	// Methods
	void allocate(std::vector<NodeBase> nodes);	//!< Allocate NodeBase elements to nodes data member
	void clearCharge();							//!< Set charge to 0 for all elements
	void clearPhi();							//!< Set phi to 0 for all elements
};