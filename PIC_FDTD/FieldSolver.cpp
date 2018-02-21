//! \file
//! \brief Implementation of FieldSolver class 
//! \author Rahul Kalampattel
//! \date Last updated February 2018

#include "FieldSolver.h"

// Default constructor
FieldSolver::FieldSolver()
{
}

// Constructor
FieldSolver::FieldSolver(Parameters *parametersList, Mesh *mesh, VectorParticle *particlesVector)
{
	// Set potential at all nodes to zero at the start of each step
	mesh->nodesVector.clearPhi();

	double h = mesh->h;

	// Gauss-Seidel solver with successive over-relaxation (SOR)
	// TODO: Enable switch statements to change solver type (GS-SOR, FFT, etc.)
	for (int i = 0; i < parametersList->maxSolverIterations; i++)
	{
		for (int j = 0; j < mesh->numNodes; j++)
		{
			// TODO: Assuming periodic BCs in the x direction, for nodes on the 
			// L boundary, use opposite node instead of left, similarly for nodes
			// on the R, same applies for the four corner nodes

			if (mesh->nodesVector.nodes[j].boundaryType == "internal")
			{
				mesh->nodesVector.nodes[j].phi = parametersList->SORparameter * 0.25 *
					((mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
					mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi) + 
					(1 - parametersList->SORparameter) * mesh->nodesVector.nodes[j].phi;
			}
		}

		// Check convergence
		if (i != 0 && i % 9 == 0)
		{
			double residualSum = 0;

			for (int j = 0; j < mesh->numNodes; j++)
			{
				// TODO: Include other nodes in calculating residual sum
				if (mesh->nodesVector.nodes[j].boundaryType == "internal")
				{
					double residual =
						(mesh->nodesVector.nodes[j].rho / parametersList->epsilon0) * h * h +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].leftNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].rightNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].topNodeID - 1].phi +
						mesh->nodesVector.nodes[mesh->nodesVector.nodes[j].bottomNodeID - 1].phi -
						4 * mesh->nodesVector.nodes[j].phi;

					residualSum += residual * residual;
				}
			}
			
			if (sqrt(residualSum / static_cast<double>(mesh->numNodes)) < parametersList->residualTolerance)
			{
				break; 
			}
		}

		// TODO: Enforce periodic BC on phi, phi(R) = phi(L)
	}

	// Electric field
	for (int i = 0; i < mesh->numNodes; i++)
	{
		// TODO: Include other nodes as well, can use centred difference across
		// boundary in the x case and for most y cases, for corner nodes the 
		// forwards or backwards difference in y are required

		if (mesh->nodesVector.nodes[i].boundaryType == "internal")
		{
			mesh->nodesVector.nodes[i].fields[0] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].leftNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].rightNodeID - 1].phi) / (2 * h);

			mesh->nodesVector.nodes[i].fields[1] = (mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].bottomNodeID - 1].phi -
				mesh->nodesVector.nodes[mesh->nodesVector.nodes[i].topNodeID - 1].phi) / (2 * h);
		}
	}
}

// Destructor
FieldSolver::~FieldSolver()
{
}