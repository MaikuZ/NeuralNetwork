/*!
  Author: MaikuZ
*/
#include "Vertex.h"
#include <cmath>
long double Vertex::getBias()
{
  return bias;
}
void Vertex::setVertex(int level, int id, int globalID, long double bias)
{
  this->level = level;
  this->id = id;
  this->globalID = globalID;
  this->bias = bias;
}
long double Vertex::sigmaFunction(long double value)
{
  return (long double)(1)/(1 + (long double)exp(-value));
}
long double Vertex::sigmaFunctionDerivative(long double value)
{
  return sigmaFunction(value)*(1-sigmaFunction(value));
}
void Vertex::setValue(long double value)
{
    this->value = value;
}
long double Vertex::getValue()
{
  return value;
}
long double Vertex::getError()
{
    return error;
}
long double Vertex::calculateValue(vector<vector<Vertex> > &Graph)
{
  long double sum = 0;
  for(auto x: In)
  {
    int id = x->from;
    int level = x->levelFrom;
    sum += Graph[level][id].getValue()*x->weight;
  }
  summedInput = sum;
  sum += bias;
  value = sigmaFunction(sum);
  return value;
}
int Vertex::getLevel()
{
  return level;
}
int Vertex::getID()
{
  return id;
}
void Vertex::addEdgeOut(Edge *edge)
{
  Out.push_back(edge);
}
void Vertex::addEdgeIn(Edge *edge)
{
  In.push_back(edge);
}
