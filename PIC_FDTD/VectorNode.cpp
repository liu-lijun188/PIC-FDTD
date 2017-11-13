//! \file
//! \brief Implementation of VectorNode class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "VectorNode.h"

// Default constructor
VectorNode::VectorNode()
{
}

// Destructor
VectorNode::~VectorNode()
{
}

// Allocate nodes to nodes attribute
void VectorNode::allocate(std::vector<NodeBase> nodes)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		Nodes tempNode(nodes[i]);
		this->nodes.push_back(tempNode);
	}
}