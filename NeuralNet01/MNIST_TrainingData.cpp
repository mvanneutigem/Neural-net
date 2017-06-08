#include "MNIST_TrainingData.h"
#include "MNISTParser.h"
#include <iostream>
using namespace std;

MNIST_TrainingData::MNIST_TrainingData(const string imageFile, const string labelFile, const int NrOfHiddenLayers) :m_NrOfLayers(NrOfHiddenLayers)
{
	m_Data = MNISTDataset();
	m_Data.Parse(imageFile.c_str(), labelFile.c_str());
	m_Width = m_Data.GetImageWidth();
	m_Height = m_Data.GetImageHeight();
	m_NrOfInputs = m_Data.GetImageCount();
	m_NrOfLayers = NrOfHiddenLayers;
}

void MNIST_TrainingData::getTopology(vector<unsigned> &topology) const
{
	if (m_Width == 0 || m_Height == 0)
		throw(std::string("invalid width and/or height"));

	for (int i = 0; i < m_NrOfLayers + 1; ++i)//+1 for the input layer
	{
		topology.push_back(m_Height * m_Width);
	}
	topology.push_back(10);//output layer
	//output of 10 neurons!!!
	return;
}

unsigned int MNIST_TrainingData::getNextInputs(vector<double> &inputVals)
{
	inputVals.clear();

	const float* imageBuffer = &m_Data.GetImageData()[m_InputCounter * m_Data.GetImageSize()];

	for (size_t j = 0; j < m_Height; ++j)
	{
		for (size_t i = 0; i < m_Width; ++i)
		{
			auto value = imageBuffer[j * m_Width + i] / 255.0f;
			inputVals.push_back(value);
		}
	}
	++m_InputCounter;

	return inputVals.size();
}

unsigned int MNIST_TrainingData::getTargetOutputs(vector<double> &targetOutputVals)
{
	targetOutputVals.clear();

	const uint8_t output = m_Data.GetCategoryData()[m_OutputCounter];
	double outputvalue = int(output);
	cout << "expected output: \n";
	
	for(auto i = 0; i < 10; ++i)
	{
		if (i == outputvalue)
		{
			targetOutputVals.push_back(1.0);
			cout << "1\n";
		}
		else
		{
			targetOutputVals.push_back(0.0);
			cout << "0\n";
		}
	}
	++m_OutputCounter;

	return targetOutputVals.size();
}
