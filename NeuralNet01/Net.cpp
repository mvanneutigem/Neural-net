#include "Net.h"
#include "Neuron.h"
#include <cassert>
#include <iostream>

Net::Net(const std::vector<unsigned int> topology)
{
	unsigned numLayers = topology.size();
	for (unsigned int layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		unsigned int numOutputs = 0;
		if (layerNum != topology.size() - 1)
			numOutputs = topology[layerNum + 1];

		m_Layers.push_back(Layer());
		for (unsigned int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)//1 bias neuron so 1 more loop
		{
			m_Layers.back().push_back(Neuron(numOutputs, neuronNum));//back gives most recent element
		}

		//force the bias neuron to output 1
		m_Layers.back().back().SetOutputValue(1.0);
	}
}

void Net::getResults(std::vector<double>& resultsVals) const
{
	resultsVals.clear();
	for (unsigned int n = 0; n < m_Layers.back().size() - 1; ++n)
	{
		resultsVals.push_back(m_Layers.back()[n].GetOutputValue());
	}
}

void Net::backProp(const std::vector<double>& targetVals)
{
	// calculate overall net error (RMS of output neuron errors)
	//RMS = root mean square
	Layer &outputLayer = m_Layers.back();
	m_error = 0.0;

	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		double delta = targetVals[n] - outputLayer[n].GetOutputValue();
		m_error += delta * delta;
	}
	m_error /= outputLayer.size() - 1;
	m_error = sqrt(m_error);//rms

	//recent average measurement:
	m_recentAverageError = (m_recentAverageError * m_recentAverageSmoothingFactor + m_error) / (m_recentAverageSmoothingFactor + 1.0);

	//calculate output layer gradients
	for (unsigned int n = 0; n < outputLayer.size() - 1; ++n)
	{
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}

	//calculate gradients on hidden layers
	//for (unsigned int layerNum = m_Layers.size() - 2; layerNum > 0; --layerNum)
	//{
	//	Layer &hiddenLayer = m_Layers[layerNum];
	//	Layer &nextLayer = m_Layers[layerNum + 1];

	//	for (unsigned int n = 0; n < hiddenLayer.size(); ++n)
	//	{
	//		hiddenLayer[n].calcHiddenGradients(nextLayer);
	//	}
	//}

	//for all layers from outputs to first hidden layer: update connection weights
	for (unsigned int layerNum = m_Layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer &layer = m_Layers[layerNum];
		Layer &prevlayer = m_Layers[layerNum - 1];

		for (unsigned int n = 0; n < layer.size() - 1; ++n)
		{
			layer[n].updateInputWeights(prevlayer);
		}
	}

}


void Net::feedForward(const std::vector<double>& inputVals)
{
	//error check if size of inputlayer is correct
	assert(inputVals.size() == m_Layers[0].size() - 1);

	//assign the input values to input neurons
	for (unsigned int i = 0; i < inputVals.size(); ++i)
	{
		m_Layers[0][i].SetOutputValue(inputVals[i]);
	}

	//forward propagation = looping through each neuron -> ask to feed forward
	for (unsigned int layerNum = 1; layerNum < m_Layers.size(); ++layerNum)
	{
		Layer &pPrevLayer = m_Layers[layerNum - 1];
		for (unsigned int n = 0; n < m_Layers[layerNum].size() - 1; ++n)
		{
			m_Layers[layerNum][n].feedForward(pPrevLayer);
		}
	}

}

