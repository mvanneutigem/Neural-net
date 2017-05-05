#include "Neuron.h"
#include <iostream>
#include <fstream>

double Neuron::eta = 0.15;//overall learning rate
double Neuron::alpha = 0.5;

void Neuron::updateInputWeights(Layer &prevLayer)
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

double Neuron::sumDOW(const Layer &nextlayer) const
{
	double sum = 0;

	//sum our contributions of the error nodes we feed
	for (unsigned int n = 0; n < nextlayer.size() - 1; ++n)
	{
		sum += m_outputWeights[n].weight * nextlayer[n].m_gradient;
	}
	return sum;
}
//
//void Neuron::calcHiddenGradients(const Layer& nextlayer)
//{
//	double dow = sumDOW(nextlayer);
//	m_gradient = dow * transferFND(m_outputVal);
//}

void Neuron::calcOutputGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	m_gradient = delta * transferFND(m_outputVal);
}

//double Neuron::transferFunction(double x)
//{
//	//make sure to use a curved function (derivative function)
//	//scale your output -> stay in range!
//
//	//tanh - output range[-1.0...1.0]
//	return tanh(x);
//}

//double Neuron::transferFunctionDerivative(double x)
//{
//	//tanh derivative (approximation)
//	return 1.0 - x*x;
//}

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