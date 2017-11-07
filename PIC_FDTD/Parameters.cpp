//! \file
//! \brief Implementation of Parameters class 
//! \author Rahul Kalampattel
//! \date Last updated October 2017

#include "Parameters.h"

// Default constructor
Parameters::Parameters()
{
}

// Constructor
Parameters::Parameters(std::string filename)
{
	initialTime = clock();
	std::ifstream inputFile(filename);	// Open input file
	
	char firstCharacter;
	std::string name;
	std::string value;

	if (inputFile.is_open())
	{
		logMessages("Reading inputs", __FILE__, __LINE__);

		while (!inputFile.eof())	// Continue until the end of the file is reached
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
		logMessages("Unable to open input file!!!", __FILE__, __LINE__);
		fileNotOpened = true;
	}
}

// Destructor
Parameters::~Parameters()
{
}

// Print raw input from valuesVector
void Parameters::printValuesVector()
{
	if (valuesVector.size() != 0)
	{
		for (size_t i = 0; i < valuesVector.size(); i++)
		{
			std::cout << "Parameter " << i + 1 << " is: " << valuesVector[i] << std::endl;
		}
		std::cout << std::endl;
	}
}

// Assign values to member variables
void Parameters::assignInputs()
{
	if (!fileNotOpened)
	{
		try
		{
			timeStep = stod(valuesVector[0]);
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for time step!!!", __FILE__, __LINE__);
		}

		try
		{
			maximumNumberOfIterations = stoi(valuesVector[1]);
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for maximum number of iterations!!!", __FILE__, __LINE__);
		}
		
		try
		{
			numberOfPatches = stoi(valuesVector[2]);
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for number of patches!!!", __FILE__, __LINE__);
		}
		
		try
		{
			particlesPerCell = stoi(valuesVector[3]);
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for particles per cell!!!", __FILE__, __LINE__);
		}

		try
		{
			meshFilePath = valuesVector[4];
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for mesh file path!!!", __FILE__, __LINE__);
		}
	}
}

// Print member variables
void Parameters::printMemberVariables()
{
	std::cout << "Time step: " << timeStep << std::endl;
	std::cout << "Maximum number of iterations: " << maximumNumberOfIterations << std::endl;
	std::cout << "Number of patches: " << numberOfPatches << std::endl;
	std::cout << "Particle per cell: " << particlesPerCell << std::endl;
	std::cout << "Mesh file path: " << meshFilePath << std::endl;
}

// Process mesh file
void Parameters::processMesh()
{
	logMessages("Extracting mesh data", __FILE__, __LINE__);
	precessingGridSU2(meshFilePath, processedMeshFile);
	readGridFromFile(processedMeshFile + ".op2", gridinfo, gridgeo);
	processingGrid(gridinfo, gridgeo);
}

// Generate Tecplot output
void Parameters::generateOutput(vector2D data, int N)
{
	logMessages("Generating Tecplot output", __FILE__, __LINE__);
	writeGridGeoTecplot(tecplotMesh, gridinfo, gridgeo);
	writeSolutionXYTecplot(tecplotSolution, data, N); 
}

// Keeps console window open
void Parameters::hitReturnToEnter()
{
	do 
	{
		std::cout << std::endl << "Press the return key to continue . . .";
	} 
	while (std::cin.get() != '\n');
}

// Log messages and warnings
void Parameters::logMessages(std::string message, std::string filename, int line)
{
	clock_t currentTime;
	if (!firstLog)
	{
		std::ofstream logFile("logFile.txt", std::ios::app);	// Open log file, 'append' write mode

		if (logFile.is_open())
		{
			currentTime = clock() - initialTime;
			logFile << static_cast<float>(1000 * currentTime) / CLOCKS_PER_SEC << "\t\t" << 
				message << " (" << filename << ", " << line << ")" << std::endl;
			logFile.close();
		}
		else
		{
			std::cout << "Unable to open log file!!!" << std::endl;
		}
		std::cout << message << std::endl;
	}
	else
	{
		std::ofstream logFile("logFile.txt", std::ios::trunc);	// Open log file, 'truncate' write mode

		if (logFile.is_open())
		{
			
			currentTime = clock() - initialTime;
			logFile << static_cast<float>(1000 * currentTime) / CLOCKS_PER_SEC << "\t\t" <<
				message << " (" << filename << ", " << line << ")" << std::endl;
			logFile.close();
		}
		else
		{
			std::cout << "Unable to open log file!!!" << std::endl;
		}
		firstLog = false;
	}

}