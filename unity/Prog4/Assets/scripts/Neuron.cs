using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using Layer = System.Collections.Generic.List<Neuron>;

public class Connection
{
    public double weight;

    public Connection()
    {
        weight = 0.5f;
    }
};

public class Neuron //: MonoBehaviour 
{

    private double m_outputVal = 0.5f;
    int m_myIndex;

    List<Connection> m_outputWeights;

    public Neuron(int numOutputs, int myIndex, ref List<double> weights)
    {
        m_outputWeights = new List<Connection>();
        m_myIndex = myIndex;
        for (int c = 0; c < numOutputs; ++c)
        {
            var connection  = new Connection();
            m_outputWeights.Add(connection);
            var tempConnection = m_outputWeights[m_outputWeights.Count -1];
            tempConnection.weight = weights[c];
            m_outputWeights[m_outputWeights.Count - 1] = tempConnection;

        }
    }

    public void SetOutputValue(double val)
    {
        m_outputVal = val;
    }

    public double GetOutputValue()
    {
        return m_outputVal;
    }

    public void feedForward(ref List<Neuron> prevLayer)
    {
        double sum = 0;
        for (int n = 0; n < prevLayer.Count; ++n)
        {
            sum += prevLayer[n].GetOutputValue() * prevLayer[n].m_outputWeights[m_myIndex].weight;
        }
        sum /= prevLayer.Count;
        //m_outputVal = transferFunction(sum);
        m_outputVal = transferFunction(sum);
    }

    double transferFunction(double x)
    {
        //make sure to use a curved function (derivative function)
        //scale your output -> stay in range!

        //tanh - output range[-1.0...1.0]
        double output = Math.Tanh(x);
        return output;
    }
}
