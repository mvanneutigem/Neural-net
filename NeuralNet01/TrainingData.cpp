#include "TrainingData.h"
#include <sstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<dirent.h>//dirent library does not come with vs download it here: http://www.softagalleria.net/dirent.php
#include <iostream>
#include <limits.h>
using namespace std;

TrainingData::TrainingData(const string setup, const int NrOfHiddenLayers):m_NrOfLayers(NrOfHiddenLayers)
{
	m_trainingDataFile.open(setup.c_str());
	string line;
	getline(m_trainingDataFile, line);
	m_Directory = line;
	getline(m_trainingDataFile, line);
	m_NrOfInputs = stoi(line);
	getline(m_trainingDataFile, line);
	m_Width = stoi(line);
	getline(m_trainingDataFile, line);
	m_Height = stoi(line);

	DIR *pDIR;
	struct dirent *entry;
	if (pDIR = opendir(m_Directory.c_str()))
	{
		while (entry = readdir(pDIR))
		{
			if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
			{
				cout << entry->d_name << "\n";
				m_TraingFilesArr.push_back(entry->d_name);
			}
		}
		closedir(pDIR);
	}
}

void TrainingData::getTopology(vector<unsigned> &topology) const
{
	if (m_Width == 0 || m_Height == 0)
		throw(std::string("invalid width and/or height"));

	for(int i = 0; i < m_NrOfLayers + 1; ++i)//+1 for the input layer
	{
		topology.push_back(m_Height * m_Width);
	}
	topology.push_back(1);//output layer
	return;
}

unsigned int TrainingData::getNextInputs(vector<double> &inputVals)
{
	inputVals.clear();

	string file = m_TraingFilesArr[m_InputCounter];
	++m_InputCounter;
	file = m_Directory + "/" + file;
	int width, height, comp;
	unsigned char* image = stbi_load(file.c_str(), &width, &height, &comp, STBI_grey);
	if (image == nullptr)
		throw(std::string("Failed to load image"));
	
	if (width != m_Width || height != m_Height)
		throw(std::string("image has incorrect width and/or height"));

	for(int i = 0; i < height * width; ++i )
	{
		auto value = image[i];
		inputVals.push_back(value);
	}
	stbi_image_free(image);

	return inputVals.size();
}

unsigned int TrainingData::getTargetOutputs(vector<double> &targetOutputVals)
{
	targetOutputVals.clear();
	if (m_trainingDataFile.eof())
		throw(std::string("incorrect number of output values found"));
	string line;
	getline(m_trainingDataFile, line);
	cout << "expected output: " + line << endl;
	double outputValue = stod(line);
	targetOutputVals.push_back(outputValue);

	return targetOutputVals.size();
}
