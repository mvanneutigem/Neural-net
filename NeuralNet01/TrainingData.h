#pragma once
#include <string>
#include <vector>
#include <fstream>

class TrainingData
{
public:
	TrainingData(const std::string setup, const int NrOfHiddenLayers);
	bool endReached(void) { return m_InputCounter >= m_NrOfInputs; }
	void getTopology(std::vector<unsigned> &topology) const;

	// Returns the number of input values read from the file:
	unsigned int getNextInputs(std::vector<double> &inputVals);
	unsigned int getTargetOutputs(std::vector<double> &targetOutputVals);

private:
	std::ifstream m_trainingDataFile;
	std::string m_Directory;
	std::vector<std::string> m_TraingFilesArr;
	int m_Width = 0;
	int m_Height = 0;
	int m_InputCounter = 0;
	int m_NrOfLayers = 0;
	int m_NrOfInputs = 0;
};

