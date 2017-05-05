#pragma once
#include <vector>
class Neuron;
typedef std::vector<Neuron> Layer;
struct Connection
{
	double weight;
	double deltaWeight;

};
//clas neuron
class Neuron
{
public:
	Neuron(unsigned int numOutputs, unsigned int myIndex);
	void SetOutputValue(double val) { m_outputVal = val; }
	double GetOutputValue() const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer& nextlayer);
	void updateInputWeights(Layer &prevLayer);

	std::vector<Connection>& getOutputWeights() { return m_outputWeights; };
private:
	//static double transferFunction(double x);
	double(*transferFN)(double) = [](double x) { return tanh(x); };
	double(*transferFND)(double) = [](double x) {return 1.0 - x*x; };
	double(*randW)() = []() { return rand() / double(RAND_MAX); };

	//static double transferFunctionDerivative(double x);
	//static double randomWeight() { return rand() / double(RAND_MAX); }
	double sumDOW(const Layer &nextlayer) const;
	double m_outputVal =  0.5f;
	int m_myIndex;
	std::vector<Connection> m_outputWeights;
	double m_gradient;
	static double eta; // [0-1] overall net training rate
	static double alpha; // [0-n] multiplier of last weight change (momentum)
};