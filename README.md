# Neural-net
A neural network that recognizes handwritten digits that I've been working on.
I started by gathering information, watching some lecturers and getting an understanding of how neural networks work.
Then I followed a few tutorials (http://www.cs.bham.ac.uk/~jxb/INC/nn.html and the tutorial by http://www.millermattson.com/dave/)and started implementing some basic training data to read in black and white images.
I started looking for some good data sets to train my network and stumbled upon the MNIST handwritten digits dataset, so I set up a new trainingdata class, and with the help of the mnist parser by Henry Tan I managed to get the network to train itself to recognize digits fairly accurately with as little neurons as possible so that my laptop can still handle it in a decent amount of time.
This also includes a small unity app with a stripped down version of the net that reads in weights and visually demonstrates the net's functionality.
