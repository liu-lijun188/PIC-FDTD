//! \file
//! \brief Implementation of VectorNode class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

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


// Set charge to 0 for all elements
void VectorNode::clearCharge()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].charge = 0;
	}
}


// Set phi to 0 for all elements
void VectorNode::clearPhi()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].phi = 0;
	}
}


// Clear fields members of nodes
void VectorNode::clearFields()
{
	for (int i = 0; i < nodes.size(); i++)
	{
		nodes[i].fields = { 0.0,0.0,0.0 };
	}
}