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
		logMessages("Reading inputs...");

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
			logMessages("Invalid argument detected for time step!!!");
		}

		try
		{
			maximumNumberOfIterations = stoi(valuesVector[1]);
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for maximum number of iterations!!!");
		}
		
		try
		{
			numberOfPatches = stoi(valuesVector[2]);
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for number of patches!!!");
		}
		
		try
		{
			particlesPerPatch = stoi(valuesVector[3]);
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for particles per patch!!!");
		}

		try
		{
			meshFilePath = valuesVector[4];
		}
		catch (std::invalid_argument&)
		{
			logMessages("Invalid argument detected for mesh file path!!!");
		}
	}
}

// Print member variables
void Parameters::printMemberVariables()
{
	std::cout << "Time step: " << timeStep << std::endl;
	std::cout << "Maximum number of iterations: " << maximumNumberOfIterations << std::endl;
	std::cout << "Number of patches: " << numberOfPatches << std::endl;
	std::cout << "Particle per patch: " << particlesPerPatch << std::endl;
	std::cout << "Mesh file path: " << meshFilePath << std::endl;
}

// Process mesh file
void Parameters::processMesh()
{
	logMessages("Extracting mesh data...");
	precessingGridSU2(meshFilePath, processedMeshFile);
	readGridFromFile(processedMeshFile + ".op2", gridinfo, gridgeo);
	processingGrid(gridinfo, gridgeo);
}

// Generate Tecplot output
void Parameters::generateOutput()
{
	writeGridGeoTecplot(tecplotMesh, gridinfo, gridgeo);

	std::vector<std::string> variableNames = { "Cell_ID_squared" };
	int N = 1;
	vector2D data;

	for (int i = 0; i < gridinfo.NCM; i++)
	{
		data.push_back(std::vector<double>());
		for (int j = 0; j<N; j++)
		{
			data[i].push_back(121);
		}
	}

	writeSolutionCellTecplot(tecplotSolution, gridinfo, gridgeo, data, variableNames, N);
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
void Parameters::logMessages(std::string message)
{
	clock_t currentTime;
	if (!firstLog)
	{
		std::ofstream logFile("logFile.txt", std::ios::app);	// Open log file, 'append' write mode

		if (logFile.is_open())
		{
			currentTime = clock() - initialTime;
			logFile << static_cast<float>(1000 * currentTime) / CLOCKS_PER_SEC << ' ' << message << std::endl;
			logFile.close();
		}
		else
		{
			std::cout << "Unable to open log file" << std::endl;
		}
		std::cout << message << std::endl;
	}
	else
	{
		std::ofstream logFile("logFile.txt", std::ios::trunc);	// Open log file, 'truncate' write mode

		if (logFile.is_open())
		{
			
			currentTime = clock() - initialTime;
			logFile << static_cast<float>(1000 * currentTime) / CLOCKS_PER_SEC << ' ' << message << std::endl;
			logFile.close();
		}
		else
		{
			std::cout << "Unable to open log file" << std::endl;
		}
		firstLog = false;
	}

}