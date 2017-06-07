#include "Neuron.h"
#include <iostream>
#include <fstream>

double Neuron::eta = 0.15;//overall learning rate
double Neuron::alpha = 0.5;

void Neuron::updateInputWeights(Layer &prevLayer) const
{
	//the weights to be updated are in the connection container in the neurons in the previous layer
	for (unsigned int n = 0; n < prevLayer.size(); ++n)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;
		auto output = neuron.GetOutputValue();

		//individual input, magnified by the gradient and train rate
		//also add momentum = a fraction of the previous delta weight
		double newDeltaWeight =	eta * output * m_gradient + alpha *oldDeltaWeight;
		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

double Neuron::sum(const Layer &nextlayer) const
{
	//hidden layer
	double sum = 0;

	//sum contributions of the error nodes fed
	for (unsigned int n = 0; n < nextlayer.size() - 1; ++n)
	{
		sum += m_outputWeights[n].weight * nextlayer[n].m_gradient;
	}
	return sum;
}

void Neuron::calcHiddenGradients(const Layer& nextlayer)
{
	double dsum = sum(nextlayer);
	m_gradient = dsum * transferFND(m_outputVal);
}

void Neuron::calcOutputGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	m_gradient = delta * transferFND(m_outputVal);
}

void Neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0;

	//sum the prev layers outputs (inputs to this)
	//include the bias neuron from prev layer

	for (unsigned n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].GetOutputValue() * prevLayer[n].m_outputWeights[m_myIndex].weight;
	}
	sum /= prevLayer.size();//divide to get output in range
	m_outputVal = transferFN(sum);
}

Neuron::Neuron(unsigned int numOutputs, unsigned int myIndex) :
	m_myIndex(myIndex)
{
	for (unsigned int c = 0; c < numOutputs; ++c)
	{
		m_outputWeights.push_back(Connection());
		m_outputWeights.back().weight = randW();
	}
}