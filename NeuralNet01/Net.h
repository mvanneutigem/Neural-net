#pragma once

#include <vector>
#include "Neuron.h"
typedef std::vector<Neuron> Layer;

//class net
class Net
{
public:
	Net(const std::vector<unsigned int> topology);
	void feedForward(const std::vector<double>& inputVals);
	void backProp(const std::vector<double>& targetVals);
	void getResults(std::vector<double>& resultsVals) const;
	double getRecentAverageError() const { return m_recentAverageError; };

	std::vector<Layer>& getLayers() { return m_Layers; };
private:
	std::vector<Layer> m_Layers;//m_layers[layernum][neuronnum]
	double m_error;
	double m_recentAverageError;
	double m_recentAverageSmoothingFactor;
};
