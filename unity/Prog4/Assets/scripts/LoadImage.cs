using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LoadImage : MonoBehaviour {

    public string url = "https://docs.unity3d.com/uploads/Main/ShadowIntro.png";
    private Color[] pixels;
    IEnumerator Start()
    {
        Texture2D tex;
        tex = new Texture2D(4, 4, TextureFormat.DXT1, false);
        WWW www = new WWW(url);
        yield return www;
        www.LoadImageIntoTexture(tex);
        //tex.SetPixels()
        //TextureScale.Bilinear(tex, 28, 28);
        //tex.Apply();
        pixels = tex.GetPixels();
        GetComponent<Renderer>().material.mainTexture = tex;
        main();

    }

    void main()
    {
        List<int> topo = new List<int>();
        GetTopology(ref topo);
        Net mnist_net = new Net(topo);

        List<double> inputVals = new List<double>();
        List<double> resultVals = new List<double>();

        GetNextInputs(ref inputVals);
        mnist_net.FeedFoward(ref inputVals);
        mnist_net.GetResults(ref resultVals);

        Debug.Log("Output:");
        int highestID = 0;
        int highest = 0;
        for (int i = 0; i < 10; ++i)
        {
            Debug.Log(resultVals[i]);
            if (resultVals[i] > highest)
            {
                highestID = i;
            }
        }
        Debug.Log("found : " + highestID);

    }

     void GetTopology(ref List<int> topology)
    {
        topology.Add(28 * 28);//inputlayer
        topology.Add(10);//outputlayer
    }

    void GetNextInputs(ref List<double> inputVals)
    {
        for (uint j = 0; j < 28; ++j)
        {
            for (uint i = 0; i < 28; ++i)
            {
                double pixel = pixels[j * 28 + i].r;
                double value = pixel;
                inputVals.Add(value);
            }
        }
    }
    
}
