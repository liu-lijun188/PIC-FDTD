//! \file
//! \brief Implementation of FieldInterpolator class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#include "FieldInterpolator.h"

// Default constructor
FieldInterpolator::FieldInterpolator()
{
}

// TODO: Large parts of the code below are similar to what is in ChargeProjector
// Potentially look at making both functions of Patch, enabling code re-use?

// Constructor
FieldInterpolator::FieldInterpolator(Parameters *parametersList,
	Mesh *mesh, VectorParticle *particlesVector)
{
	particlesVector->clearFields();

	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// TODO: Can change all of the below to references to avoid copying large 
		// amounts of data for each calculation

		int cellID = particlesVector->particleVector[i].cellID - 1;
		int nodeID_0 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[0] - 1;
		int nodeID_1 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[1] - 1;
		int nodeID_2 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[2] - 1;
		int nodeID_3 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[3] - 1;

		double left = mesh->cellsVector.cells[cellID].left;
		double right = mesh->cellsVector.cells[cellID].right;
		double top = mesh->cellsVector.cells[cellID].top;
		double bottom = mesh->cellsVector.cells[cellID].bottom;

		double hSquared = mesh->h * mesh->h;

		double x = particlesVector->particleVector[i].position[0];
		double y = particlesVector->particleVector[i].position[1];

		std::string firstNodePosition = mesh->cellsVector.cells[cellID].firstNodePosition;
		double charge = particlesVector->particleVector[i].basic.q;

		if (firstNodePosition == "BL")
		{
			for (int j = 0; j < 4; j++)
			{
				particlesVector->particleVector[i].fields[j] =
					mesh->nodesVector.nodes[nodeID_0].fields[j] * (right - x) * (top - y) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].fields[j] * (x - left) * (top - y) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].fields[j] * (x - left) * (y - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].fields[j] * (right - x) * (y - bottom) / hSquared;
			}
		}
		else if (firstNodePosition == "BR")
		{
			for (int j = 0; j < 4; j++)
			{
				particlesVector->particleVector[i].fields[j] =
					mesh->nodesVector.nodes[nodeID_0].fields[j] * (x - left) * (top - y) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].fields[j] * (x - left) * (y - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].fields[j] * (right - x) * (y - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].fields[j] * (right - x) * (top - y) / hSquared;
			}
		}
		else if (firstNodePosition == "TR")
		{
			for (int j = 0; j < 4; j++)
			{
				particlesVector->particleVector[i].fields[j] =
					mesh->nodesVector.nodes[nodeID_0].fields[j] * (x - left) * (y - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].fields[j] * (right - x) * (y - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].fields[j] * (right - x) * (top - y) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].fields[j] * (x - left) * (top - y) / hSquared;
			}
		}
		else if (firstNodePosition == "TL")
		{
			for (int j = 0; j < 4; j++)
			{
				particlesVector->particleVector[i].fields[j] =
					mesh->nodesVector.nodes[nodeID_0].fields[j] * (right - x) * (y - bottom) / hSquared +
					mesh->nodesVector.nodes[nodeID_1].fields[j] * (right - x) * (top - y) / hSquared +
					mesh->nodesVector.nodes[nodeID_2].fields[j] * (x - left) * (top - y) / hSquared +
					mesh->nodesVector.nodes[nodeID_3].fields[j] * (x - left) * (y - bottom) / hSquared;
			}
		}

		// Calculate Lorentz force
		// TODO: Change to vector notation rather than components, then use 
		// proper cross product for magnetic field component
		// TODO: Consider moving this into ParticlePusher to save on repetition
		// (no need to calculate the force in two steps...)
		for (int j = 0; j < 2; j++)
		{
		particlesVector->particleVector[i].lorentz[j] = charge *
			(particlesVector->particleVector[i].fields[j] + particlesVector->particleVector[i].velocity[j] *
				particlesVector->particleVector[i].fields[j+2]);
		}
	}
}


// Destructor
FieldInterpolator::~FieldInterpolator()
{
}