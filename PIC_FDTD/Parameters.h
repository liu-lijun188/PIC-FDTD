#pragma once

#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "GRID/grid.hpp"

using namespace std;

class Parameters
{
private:
	vector<string> valuesVector;
	bool fileNotOpened = false;
	bool firstLog = true;
	clock_t initialTime, currentTime;

public:
	Parameters();
	Parameters(string filename);	// Default constructor, reads input file and dumps data in valuesVector
	~Parameters();

	void printValuesVector();		// Print raw input from valuesVector
	void distributeInputs();		// Assign values to member variables
	void printMemberVariables();	// Print member variables
	void hitReturnToEnter();		// Keeps console window open
	void logMessages(string message);

	double timeStep;
	int maximumNumberOfIterations, numberOfPatches, particlesPerPatch;
	string meshFilePath;
	string processedMesh = "processedMesh";

};