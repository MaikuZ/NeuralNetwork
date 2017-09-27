/*!
  Author: MaikuZ
*/
#ifndef VERTEX_H_INCLUDED
#define VERTEX_H_INCLUDED

#include <vector>
#include "Edge.h"
using namespace std;
class Vertex
{
    friend class Network;
private:
    int level;//0 - means input
    int id;
    int globalID;
    long double bias;
    long double summedInput = 0;
    long double value = -1;
    long double error = 0;
    vector<Edge*> Out;
    vector<Edge*> In;
public:

    long double getValue();
    long double getError();
    long double getBias();
    int getID();
    int getLevel();

    void setVertex(int level, int id, int globalID,long double bias);
    void setValue(long double value);

    long double calculateValue(vector<vector<Vertex> > &Graph);

    void addEdgeOut(Edge *edge);
    void addEdgeIn(Edge *edge);

    static long double sigmaFunction(long double value);
    static long double sigmaFunctionDerivative(long double value);
};


#endif // VERTEX_H_INCLUDED
