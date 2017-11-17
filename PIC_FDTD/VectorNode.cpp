//! \file
//! \brief Implementation of VectorNode class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#include "VectorNode.h"

// Default constructor
VectorNode::VectorNode()
{
}


// Destructor
VectorNode::~VectorNode()
{
}


// Allocate NodeBase elements to nodes data member
void VectorNode::allocate(std::vector<NodeBase> nodes)
{
	for (int i = 0; i < nodes.size(); i++)
	{
		Nodes tempNode(nodes[i]);
		this->nodes.push_back(tempNode);
	}
}