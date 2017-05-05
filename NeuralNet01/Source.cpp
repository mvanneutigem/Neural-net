#include <vector>
#include <iostream>
#include "Net.h"
#include "TrainingData.h"
#include "MNIST_TrainingData.h"
using namespace std;

// neural net project
// mnist parser by Henry Tan
// implementation based on http://www.cs.bham.ac.uk/~jxb/INC/nn.html and the tutorial by http://www.millermattson.com/dave/
// adapted to work for mnist image dataset

int main()
{
	//layout of setupfile:
	//directory path
	//image width
	//image height
	//nr of outputs
	//expected output list enter seperated

	////OLD
	//TrainingData trainingData("./resources/setupset04.txt", 0);//integer to set amount of hidden layers

	//vector<unsigned> topology;
	//trainingData.getTopology(topology);
	//Net myNet(topology);

	////training net
	//vector<double> inputValues;
	//vector<double> targetValues;
	//vector<double> resultsValues;

	////while not end of trainingdata
	//while(!trainingData.endReached())
	//{
	//	//		get new inputdata and feedforward
	//	trainingData.getNextInputs(inputValues);
	//	myNet.feedForward(inputValues);
	//	//		collect the nets output results
	//	myNet.getResults(resultsValues);
	//	std::cout << "achieved output: " + std::to_string(resultsValues[0]) << endl;
	//	//		tell the net what the outputs should've been
	//	trainingData.getTargetOutputs(targetValues);
	//	myNet.backProp(targetValues);
	//}

	//file for data
	//ofstream output;
	//output.open("output.csv");

	//new
	MNIST_TrainingData mnistTraining("./resources/mnist/train-images.idx3-ubyte", "./resources/mnist/train-labels.idx1-ubyte", 0);//integer to set amount of hidden layers

	vector<unsigned> topo;
	mnistTraining.getTopology(topo);
	Net MNIST_NET(topo);

	//training net
	vector<double> inputVals;
	vector<double> targetVals;
	vector<double> resultsVals;

	//while not end of trainingdata
	while (!mnistTraining.endReached())
	{
		//		get new inputdata and feedforward
		mnistTraining.getNextInputs(inputVals);
		MNIST_NET.feedForward(inputVals);
		//		collect the nets output results
		MNIST_NET.getResults(resultsVals);
		std::cout << "achieved output: \n";
		float high = 0;
		int id = 0;
		for(auto i = 0; i < resultsVals.size(); ++i)
		{
			cout << std::to_string(resultsVals[i]) << endl;
			if (resultsVals[i] > high)
			{
				high = resultsVals[i];
				id = i;
			}
		}
		//output << "achieved output:\t" << std::to_string(resultsVals[id]) << "\n";

		//		tell the net what the outputs should've been
		mnistTraining.getTargetOutputs(targetVals);

		//for(auto t : targetVals)
		//{
		//	if (t > 0)
		//	{
		//		output << "expected output:\t" << std::to_string(targetVals[t]) << "\n\n";
		//	}
		//}

		MNIST_NET.backProp(targetVals);
	}

	ofstream finalweights;
	finalweights.open("finalweights3.txt");

	auto layers = MNIST_NET.getLayers();
	int amount = 785;
	for (auto i = 0; i < amount; ++i)
	{
		for(auto n = 0 ; n < MNIST_NET.getLayers()[0][i].getOutputWeights().size(); ++n)
		{
			finalweights << std::to_string(MNIST_NET.getLayers()[0][i].getOutputWeights()[n].weight) << "\n";

		}
	}
	for (auto i = 0; i < 10; ++i)
	{
		for (auto n = 0; n < MNIST_NET.getLayers()[1][i].getOutputWeights().size(); ++n)
		{
			finalweights << std::to_string(MNIST_NET.getLayers()[1][i].getOutputWeights()[n].weight) << "\n";

		}
	}
	finalweights.close();

	//output.close();
	cin.get();
}