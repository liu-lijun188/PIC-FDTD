//! \file
//! \brief Implementation of ChargeProjector class 
//! \author Rahul Kalampattel
//! \date Last updated November 2017

#include "ChargeProjector.h"

// Default constructor
ChargeProjector::ChargeProjector()
{
}

// Constructor
ChargeProjector::ChargeProjector(Parameters *parametersList,
	Mesh *mesh, VectorParticle *particlesVector)
{
	// ***
	// TODO: Method to set charge at all nodes to zero at the start of each step
	// ***


	for (int i = 0; i < particlesVector->numParticles; i++)
	{
		// Can change all of the below to references to avoid copying large amounts
		// of data for each calculation

		int cellID = particlesVector->particleVector[i].cellID;
		int nodeID_0 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[0];
		int nodeID_1 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[1];
		int nodeID_2 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[2];
		int nodeID_3 = mesh->cellsVector.cells[cellID].connectivity.nodeIDs[3];

		double left = mesh->cellsVector.cells[cellID].left;
		double right = mesh->cellsVector.cells[cellID].right;
		double top = mesh->cellsVector.cells[cellID].top;
		double bottom = mesh->cellsVector.cells[cellID].bottom;
		double width = mesh->cellsVector.cells[cellID].width;
		double height = mesh->cellsVector.cells[cellID].height;
		double x = particlesVector->particleVector[i].position[0];
		double y = particlesVector->particleVector[i].position[1];

		std::string firstNodePosition = mesh->cellsVector.cells[cellID].firstNodePosition;
		double charge = particlesVector->particleVector[i].basic.q;

		if (firstNodePosition == "BL")
		{
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (right - x) * (top - y) / (width * height);
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (x - left) * (top - y) / (width * height);
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (x - left) * (y - bottom) / (width * height);
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (right - x) * (y - bottom) / (width * height);

		}
		else if (firstNodePosition == "BR")
		{
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (x - left) * (top - y) / (width * height);
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (x - left) * (y - bottom) / (width * height);
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (right - x) * (y - bottom) / (width * height);
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (right - x) * (top - y) / (width * height);
		}
		else if (firstNodePosition == "TR")
		{
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (x - left) * (y - bottom) / (width * height);
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (right - x) * (y - bottom) / (width * height);
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (right - x) * (top - y) / (width * height);
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (x - left) * (top - y) / (width * height);
		}
		else if (firstNodePosition == "TL")
		{	
			mesh->nodesVector.nodes[nodeID_0].charge += charge * (right - x) * (y - bottom) / (width * height);
			mesh->nodesVector.nodes[nodeID_1].charge += charge * (right - x) * (top - y) / (width * height);
			mesh->nodesVector.nodes[nodeID_2].charge += charge * (x - left) * (top - y) / (width * height);
			mesh->nodesVector.nodes[nodeID_3].charge += charge * (x - left) * (y - bottom) / (width * height);
		}
	}
}


// Destructor
ChargeProjector::~ChargeProjector()
{
}