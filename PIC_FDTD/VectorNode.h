//! \file
//! \brief Definition of VectorNode class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#pragma once

#include "Nodes.h"

//! \class VectorNode
//! \brief Definition
class VectorNode
{
public:
	VectorNode();	//!< Default constructor
	~VectorNode();	//!< Destructor

	vector<Nodes> nodesVector;
};