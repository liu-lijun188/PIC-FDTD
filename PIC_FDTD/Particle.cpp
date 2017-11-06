//! \file
//! \brief Implementation of Particle class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Particle.h"

Particle::Particle()
{
}

Particle::Particle(Parameters *parametersList, int patchID, int cellID, int particleID)
{
	parametersList->logMessages("Generating particle " + std::to_string(particleID) + 
		" in cell " + std::to_string(cellID) + " in patch " + std::to_string(patchID),
		__FILE__, __LINE__);
	
	double left, right, top, bottom;

	// Only need to check two opposite nodes to find left, right, top and bottom,
	// however in order to be sure that a set of nodes contains two opposites, 
	// need at least three of them (two opposites plus one adjacent, hence i<3)
	for (int i = 0; i < 3; i++)	
	{
		int nodeID = parametersList->gridgeo.cells[cellID].connectivity.nodeIDs[i] - 1;
		// The nodeIDs are indexed from 1, but the nodes vector from 0, hence the -1 above

		if (i == 0)
		{
			left = parametersList->gridgeo.nodes[nodeID].geometry.X.element(0, 0);
			right = left;
			top = parametersList->gridgeo.nodes[nodeID].geometry.X.element(1, 0);
			bottom = top;
		}
		else
		{
			double x = parametersList->gridgeo.nodes[nodeID].geometry.X.element(0, 0);
			double y = parametersList->gridgeo.nodes[nodeID].geometry.X.element(1, 0);

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
	position.push_back((left + right) / 2);
	position.push_back((top + bottom) / 2);

	// Generate Tecplot output
	parametersList->generateOutput(position);
}

Particle::~Particle()
{
}