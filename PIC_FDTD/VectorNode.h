//! \file
//! \brief Definition of VectorNode class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

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
};