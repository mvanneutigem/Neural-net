using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;
//using Layer = System.Collections.Generic.List<Neuron>;

public class Net //: MonoBehaviour
{
    private List<List<Neuron>> m_Layers = new List<List<Neuron>>();

    public Net(List<int> topology)
    {
        Debug.Log("making net");
        string line;
        StreamReader thereader = new StreamReader("../prog4/Assets/resources/finalweights2.txt", Encoding.Default);


        int numLayers = topology.Count;
        for (int layerNum = 0; layerNum < numLayers; ++layerNum)
        {
            int numOutputs = 0;
            if (layerNum != topology.Count - 1)
                numOutputs = topology[layerNum + 1];

            var layer = new List<Neuron>();
            m_Layers.Add(layer);
            for (int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)//1 bias neuron so 1 more loop
            {
                List<double> weights = new List<double>();
                for (int i = 0; i < 10; ++i)
                {
                    line = thereader.ReadLine();
                    double weight = 0;
                    if (line != null)
                    {
                        weight = double.Parse(line, System.Globalization.CultureInfo.InvariantCulture);
                    }
                    else
                    {
                        
                    }
                    weights.Add(weight);
                }
                

                m_Layers[m_Layers.Count - 1].Add(new Neuron(numOutputs, neuronNum, ref weights));//back gives most recent element
            }

            //force the bias neuron to output 1
            m_Layers[m_Layers.Count - 1][m_Layers[m_Layers.Count - 1].Count - 1].SetOutputValue(1.0);
        }
        thereader.Close();
    }

    public void FeedFoward(ref List<double> inputVals)
    {
        //set input vals
        for (int i = 0; i < inputVals.Count; ++i)
        {
            m_Layers[0][i].SetOutputValue(inputVals[i]);
        }

        //feed 
        for (int layerNum = 1; layerNum < m_Layers.Count; ++layerNum)
        {
            List<Neuron> pPrevLayer = m_Layers[layerNum - 1];
            for (int n = 0; n < m_Layers[layerNum].Count - 1; ++n)
            {
                m_Layers[layerNum][n].feedForward(ref pPrevLayer);
            }
        }
    }

    public void GetResults(ref List<double> resultsVals)
    {
    
        resultsVals.Clear();
    	for (int n = 0; n<m_Layers[m_Layers.Count - 1].Count - 1; ++n)
    	{
    		resultsVals.Add(m_Layers[m_Layers.Count - 1][n].GetOutputValue());
    	}
    }
}
