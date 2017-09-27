/*!
  Author: MaikuZ
*/
#include "NeuralNetwork.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <random>
#include <iostream>

///WIP
string Network::toString()
{
  for(int i = 0;i < Graph[0].size();i++)
    cout<<Graph[0][i].getBias()<<endl;
  return "";
}


void Network::setInput(vector<int>&V)
{
  for(int i = 0;i < V.size();i++)
  {
    if(i > Graph[0].size())
      return;
    Graph[0][i].setValue(V[i]);
  }
}

Network::~Network()
{
  for(auto x: Graph)
  {
    for(auto y: x)
    {
      for(auto z: y.Out)
        delete z;
    }
  }
}

///Back propagation. phi is learning rate.
void Network::propagate(long double phi)
{
  for(int i = 1;i < Graph.size();i++)
  {
    for(int j = 0;j < Graph[i].size();j++)
    {
      Vertex &current = Graph[i][j];
      for(auto x: current.In)
      {
        Vertex &prev = Graph[i-1][x->from];

        long double toAdd =  phi * current.getError() * prev.getValue();
        current.bias += phi * current.getError();
        x->weight += toAdd;
      }
    }
  }
}

///Calculates error for every vertex in the graph.
void Network::calculateError(vector<long double> ExpectedValues)
{
  for(int i = 0;i < min(ExpectedValues.size(),Graph.back().size());i++)
  {
    //cout<<i<<" : ";
    Graph.back()[i].error = (ExpectedValues[i] - Graph.back()[i].value) * Vertex::sigmaFunctionDerivative(Graph.back()[i].value);
    //cout<<Graph.back()[i].error<<":"<<Graph.back()[i].value<<endl;
  }
  //cout<<endl;
  for(int i = Graph.size() - 2;i >= 1;i--)
  {
    for(int j = 0;j < Graph[i].size();j++)
    {
      Vertex &current = Graph[i][j];
      current.error = 0;
      for(auto x: current.Out)
      {
        current.error += Graph[i+1][x->to].error * x->weight * Vertex::sigmaFunctionDerivative(current.value);
      }
    }
  }
}

///WIP
///This function is meant to create a new neural network that will be similar to both of its parents.
///Meant for genetic algorithms.
Network::Network(Network &firstParent,Network &secondParent,long double chanceForMutation)
{
  Graph.resize(firstParent.Graph.size());
  //cout<<Graph.size()<<":::::::::"<<endl;
  for(int i = 0;i < Graph.size();i++)
  {
    Graph[i].resize(firstParent.Graph[i].size());
  }


  int globID = 0;
  for(int i = 0;i < Graph.size();i++)
  {
    for(int j = 0;j < Graph[i].size();j++)
    {
      long double newBias;
      long double lBias = firstParent.Graph[i][j].getBias();
      long double rBias = secondParent.Graph[i][j].getBias();
      int weightForL = rand()%100;
      int weightForR = 100-weightForL;
      newBias = (lBias*weightForL + rBias*weightForR)/100;

      int inHundredChanceForMutation = 100*chanceForMutation;
      if(rand()%100 < inHundredChanceForMutation)///Then mutate
      {
        newBias *= 1 + ((long double)(50-rand()%100)/(long double)100);
      }
      Graph[i][j].setVertex(j,i,globID++,newBias);
    }
  }
  for(int i = 0;i < Graph.size()-1;i++)
  {
    for(int j = 0;j < Graph[i].size();j++)
    {
      for(int k = 0;k < firstParent.Graph[i][j].Out.size();k++)
      {
        int weightForL = rand()%100;
        int weightForR = 100-weightForL;
        long double newWeight;
        Edge* lEdge = firstParent.Graph[i][j].Out[k];
        Edge* rEdge = secondParent.Graph[i][j].Out[k];

        newWeight = (long double)(weightForL*lEdge->weight + weightForR*rEdge->weight)/100;
      //  cout<<newWeight<<"!!!"<<endl;
        int inHundredChanceForMutation = 100*chanceForMutation;
        if(rand()%100 < inHundredChanceForMutation)///Then mutate
        {
          newWeight *= 1 + ((long double)(50-rand()%100)/(long double)100);
        }
        int levelFrom = i;
        int levelTo = i+1;
        int from = j;
        int to = lEdge->to;

        Edge *edge  = new Edge(levelFrom,from,levelTo,to,newWeight);

        Graph[levelFrom][from].addEdgeOut(edge);
        Graph[levelTo][to].addEdgeIn(edge);
      }
    }
  }

}
vector<long double> Network::getOutput()
{
  vector<long double> V;
  for(auto x: Graph.back())
  {
    V.push_back(x.getValue());
  }
  return V;
}
void Network::calculateValues()
{
  for(int i = 1;i < Graph.size();i++)
  {
    for(int j = 0;j < Graph[i].size();j++)
    {
      Graph[i][j].calculateValue(Graph);
    }
  }
}
Network::Network(vector<int> HiddenSizes,int InputSize ,int OutputSize)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(-1, 1);

  Graph.resize(2+HiddenSizes.size());
  Graph[0].resize(InputSize);
  Graph.back().resize(OutputSize);


  for(int i = 0;i < HiddenSizes.size();i++)
  {
    Graph[i+1].resize(HiddenSizes[i]);
  }


  int globID = 0;
  for(int i = 0;i < Graph.size();i++)
  {
    for(int j = 0;j < Graph[i].size();j++)
    {
      Graph[i][j].setVertex(j,i,globID++,0.2234234 + 1/(rand()%100+1));
    }
  }

  for(int i = 0;i < Graph.size()-1;i++)
  {
    for(int j = 0;j < Graph[i].size();j++)
    {
      for(int k = 0;k < Graph[i+1].size();k++)
      {
        Edge *edge  = new Edge(i,j,i+1,k,dis(gen));
        Graph[i][j].addEdgeOut(edge);
        Graph[i+1][k].addEdgeIn(edge);
      }
    }
  }

}
