//! \file
//! \brief Implementation of Parameters class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Parameters.h"

Parameters::Parameters()
{
}

Parameters::Parameters(string filename)
{
	initialTime = clock();
	ifstream inputFile(filename);	// Open input file
	
	char firstCharacter;
	string name;
	string value;

	if (inputFile.is_open())
	{
		logMessages("Processing parameters...");

		while (!inputFile.eof())	// Until the end of the file is reached
		{
			// Check what the first character in each line is
			firstCharacter = static_cast<char>(inputFile.get());

			// Check for commented or empty lines
			if (firstCharacter == '%' || firstCharacter == '\n')
			{
				inputFile.ignore(256, '\n');
			}
			// Store values in a string vector, names and values are space separated
			else
			{
				inputFile >> name >> value;
				valuesVector.push_back(value);
				inputFile.ignore(256, '\n');
			}
		}
		inputFile.close();
	}
	else
	{
		logMessages("Unable to open input file");
		fileNotOpened = true;
	}
}

Parameters::~Parameters()
{
}

void Parameters::printValuesVector()
{
	if (valuesVector.size() != 0)
	{
		for (size_t i = 0; i < valuesVector.size(); i++)
		{
			cout << "Parameter " << i + 1 << " is: " << valuesVector[i] << endl;
		}
		cout << endl;
	}
}

void Parameters::distributeInputs()
{
	if (!fileNotOpened)
	{
		try
		{
			timeStep = stod(valuesVector[0]);
		}
		catch (invalid_argument&)
		{
			logMessages("Invalid argument detected for time step!!!");
		}

		try
		{
			maximumNumberOfIterations = stoi(valuesVector[1]);
		}
		catch (invalid_argument&)
		{
			logMessages("Invalid argument detected for maximum number of iterations!!!");
		}
		
		try
		{
			numberOfPatches = stoi(valuesVector[2]);
		}
		catch (invalid_argument&)
		{
			logMessages("Invalid argument detected for number of patches!!!");
		}
		
		try
		{
			particlesPerPatch = stoi(valuesVector[3]);
		}
		catch (invalid_argument&)
		{
			logMessages("Invalid argument detected for particles per patch!!!");
		}

		try
		{
			meshFilePath = valuesVector[4];
		}
		catch (invalid_argument&)
		{
			logMessages("Invalid argument detected for mesh file path!!!");
		}
	}
}

void Parameters::printMemberVariables()
{
	cout << "Time step: " << timeStep << endl;
	cout << "Maximum number of iterations: " << maximumNumberOfIterations << endl;
	cout << "Number of patches: " << numberOfPatches << endl;
	cout << "Particle per patch: " << particlesPerPatch << endl;
	cout << "Mesh file path: " << meshFilePath << endl;
	precessingGridSU2(meshFilePath, processedMesh);
	readGridFromFile(processedMesh + ".op2", gridinfo, gridgeo);
}

void Parameters::hitReturnToEnter()
{
	do {
		cout << endl << "Press the return key to continue . . .";
	} while (cin.get() != '\n');
}

void Parameters::logMessages(string message)
{
	if (!firstLog)
	{
		ofstream logFile("logFile.txt", ios::app);	// Open log file

		if (logFile.is_open())
		{
			currentTime = clock() - initialTime;
			logFile << static_cast<float>(1000 * currentTime) / CLOCKS_PER_SEC << ' ' << message << endl;
			logFile.close();
		}
		else
		{
			cout << "Unable to open log file" << endl;
		}
		cout << message << endl;
	}
	else
	{
		ofstream logFile("logFile.txt", ios::trunc);	// Open log file

		if (logFile.is_open())
		{
			
			currentTime = clock() - initialTime;
			logFile << static_cast<float>(1000 * currentTime) / CLOCKS_PER_SEC << ' ' << message << endl;
			logFile.close();
		}
		else
		{
			cout << "Unable to open log file" << endl;
		}
		firstLog = false;
	}

}