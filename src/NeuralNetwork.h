/*!
  Author: MaikuZ
*/
#ifndef NEURALNETWORK_H_INCLUDED
#define NEURALNETWORK_H_INCLUDED



#include <vector>
#include "Vertex.h"
#include <string>
using namespace std;



class Network
{
private:
    vector<vector<Vertex> > Graph;
public:
    ///Use in this order{
    void setInput(vector<int> &V);
    void calculateValues();
    void calculateError(vector<long double> ExpectedValues);
    void propagate(long double phi);
    ///}

    vector<long double> getOutput();

    string toString();

    Network(vector<int> HiddenSizes,int InputSize = 16*16*3,int OutputSize = 1);
    Network(Network &firstParent,Network &secondParent,long double chanceForMutation);
    ~Network();

};
#endif
