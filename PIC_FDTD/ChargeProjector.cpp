//! \file
//! \brief Implementation of ChargeProjector class 
//! \author Rahul Kalampattel
//! \date Last updated March 2018

#include "ChargeProjector.h"

// Default constructor
ChargeProjector::ChargeProjector()
{
}

// Constructor
ChargeProjector::ChargeProjector(Parameters *parametersList,
	Mesh *mesh, VectorParticle *particlesVector)
{
	// Set charge at all nodes to zero at the start of each step
	mesh->nodesVector.clearCharge();

	double hSquared = mesh->h * mesh->h;

	// Project charge to nodes
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
		
		double x = particlesVector->particleVector[i].position[0];
		double y = particlesVector->particleVector[i].position[1];

		std::string firstNodePosition = mesh->cellsVector.cells[cellID].firstNodePosition;
		double charge = particlesVector->particleVector[i].basic.q;

		if (firstNodePosition == "BL")
		{
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (right - x) * (top - y) / hSquared;
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (x - left) * (top - y) / hSquared;
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (x - left) * (y - bottom) / hSquared;
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (right - x) * (y - bottom) / hSquared;

		}
		else if (firstNodePosition == "BR")
		{
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (x - left) * (top - y) / hSquared;
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (x - left) * (y - bottom) / hSquared;
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (right - x) * (y - bottom) / hSquared;
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (right - x) * (top - y) / hSquared;
		}
		else if (firstNodePosition == "TR")
		{
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (x - left) * (y - bottom) / hSquared;
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (right - x) * (y - bottom) / hSquared;
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (right - x) * (top - y) / hSquared;
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (x - left) * (top - y) / hSquared;
		}
		else if (firstNodePosition == "TL")
		{	
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (right - x) * (y - bottom) / hSquared;
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (right - x) * (top - y) / hSquared;
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (x - left) * (top - y) / hSquared;
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (x - left) * (y - bottom) / hSquared;
		}
	}

	// Calculate charge density (charge / cell area)
	for (int i = 0; i < mesh->numNodes; i++)
	{
		mesh->nodesVector.nodes[i].rho = mesh->nodesVector.nodes[i].charge / hSquared;
		
		// Account for fixed neutralising (background) charge (???)
		mesh->nodesVector.nodes[i].rho -= ((particlesVector->numParticles * parametersList->charge) / mesh->numCells);
	}

	// Account for periodic BCs 
	for (int i = 0; i < mesh->numNodes; i++)
	{
		if (parametersList->xBC == "periodic")
		{
			if (mesh->nodesVector.nodes[i].boundaryType == "TL" ||
				mesh->nodesVector.nodes[i].boundaryType == "L" ||
				mesh->nodesVector.nodes[i].boundaryType == "BL")
			{
				mesh->nodesVector.nodes[i].rho = 0.5 * (mesh->nodesVector.nodes[i].rho +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].rho);
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicXNodeID - 1].rho =
					mesh->nodesVector.nodes[i].rho;
			}
		}
		if (parametersList->yBC == "periodic")
		{
			if (mesh->nodesVector.nodes[i].boundaryType == "TL" ||
				mesh->nodesVector.nodes[i].boundaryType == "T" ||
				mesh->nodesVector.nodes[i].boundaryType == "TR")
			{
				mesh->nodesVector.nodes[i].rho = 0.5 * (mesh->nodesVector.nodes[i].rho +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].rho);
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].periodicYNodeID - 1].rho =
					mesh->nodesVector.nodes[i].rho;
			}
		}

	}
	parametersList->logBrief("Charge projector exited", 1);
}


// Destructor
ChargeProjector::~ChargeProjector()
{
}