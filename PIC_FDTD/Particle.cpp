//! \file
//! \brief Implementation of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Particle.h"

// Default constructor
Particle::Particle()
{
}

// Constructor
Particle::Particle(Parameters *parametersList, Mesh *mesh, int patchID, int cellID, int particleID)
{
	parametersList->logMessages("Generating particle " + std::to_string(particleID) + 
		" in cell " + std::to_string(cellID) + " in patch " + std::to_string(patchID),
		__FILE__, __LINE__);
	
	this->particleID = particleID;
	this->cellID = cellID;

	// Only need to check two opposite nodes to find left, right, top and bottom,
	// however in order to be sure that a set of nodes contains two opposites, 
	// need at least three of them (two opposites plus one adjacent, hence i<3)
	for (int i = 0; i < 3; i++)	
	{
		int nodeID = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[i] - 1;
		// The nodeIDs are indexed from 1, but the nodes vector from 0, hence the -1 above

		if (i == 0)
		{
			left = mesh->nodesVector.nodes[nodeID].geometry.X.element(0, 0);
			right = left;
			top = mesh->nodesVector.nodes[nodeID].geometry.X.element(1, 0);
			bottom = top;
		}
		else
		{
			double x = mesh->nodesVector.nodes[nodeID].geometry.X.element(0, 0);
			double y = mesh->nodesVector.nodes[nodeID].geometry.X.element(1, 0);

			if (x < left)
			{
				left = x;
			}
			else if (x > right)
			{
				right = x;
			}
			if (y < bottom)
			{
				bottom = y;
			}
			else if (y > top)
			{
				top = y;
			}
		}
	}

	// Place particle in middle of cell
	position.push_back((left + right) / 2);	// x
	position.push_back((top + bottom) / 2); // y
	
	velocity.push_back(-0.1); // u
	velocity.push_back(0); // v
}

// Destructor
Particle::~Particle()
{
}