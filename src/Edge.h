/*!
  Author: MaikuZ
*/
#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED


class Edge
{
    friend class Vertex;
    friend class Network;
private:
    int levelFrom;
    int from;
    int levelTo;
    int to;
    long double weight;
public:
    Edge(int levelFrom,int from, int levelTo,int to, long double weight);
};
#endif // EDGE_H_INCLUDED
