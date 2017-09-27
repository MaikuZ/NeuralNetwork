# NeuralNetwork
Neural Network written in C++ with the purpose of recognizing digits. 


In src are all the classes already written and ready to use to create a neural network. The amount of hiddenLayers and size of each of the layers is defined at initialization. The sigmoid function is hard-coded. The weights and biases are set to be random. There is no way to safe the neural network to a file yet. These features are something that I'd like to create in the future.

Simple usage:
```
//Include the header
#include "src/NeuralNetwork.h"


//Initialize the network. sizeOf1stHiddenLayer, inputSize, outputSize etc. are int's
Network network (vector<int> {sizeOf1stHiddenLayer,sizeOf2ndHiddenLayer,...,sizeOfNthHiddenLayer},inputSize,outputSize);


//Set input layer, it takes as an argument a vector of ints representing the input values of the corresponding input neurons.
network.setInput(vector<int> {int1,int2,int3,...,intN});


//Calculate the values at each vertex
network.calculateValues();


//Get the output of the network
vector<long double> results = network.getOutput();


//If you want to teach your network you need first to calculate error for each vertex
//double1,...,doubleN are the expected values of the output neurons


network.calculateError(vector<long double> {double1,double2,...,doubleN});


//Then you can let the back-propagation make the work of teaching it.
//phi is the learning rate. I personally found 0.2 to be working well enough
network.propagate(phi);

```

main.cpp was created to show the abilities of these classes as well as to test it. It is a neural network that is first created, then taught using 90% of the digits in [data0,...,data9] files and then tested using the rest 10% of the digits and at the end the accuracy of the network is displayed. Typically it's about 86% of accuracy as it depends on how well the initial weights were chosen(which is random).

An example of the output of main.cpp

```
Taught using 9000 examples.
Tested using 1000 examples.
CORRECT : 861 WRONG : 139
accuracy : 86.1%

Process returned 0 (0x0)   execution time : 35.382 s
Press ENTER to continue.
```

To make it work, simply compile main.cpp with the source files from src and also make sure that the files data0 to data9 are in the executive folder. The files data0 and data9 have to be downloaded from http://yann.lecun.com/exdb/mnist/ 

I hope that this repository might be of help to someone :) Even if just a tiny bit.
