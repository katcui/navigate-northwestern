/*graph.h*/

//
// Graph class using adjacency list representation. Edges
// are directed, so building an undirected graph requires
// adding edges in both directions. No limit on graph size,
// but multi-edges (multiple edges between the same two
// vertices) are not allowed.
// 
// For this implementation of graph, the vertices are 
// long long, and the weights are doubles.  Example:
// 
//   graph  G;
//   G.addVertex(129850);
//   G.addVertex(552985);
//   G.addEdge(129850, 552985, 99.99);
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>

#include "nodes.h"
#include "footways.h"

using namespace std;


class graph
{
private:
  vector<long long>    Vertices;
  map<long long, int>  Vertex2Index;
  vector<map<int, double>> Edges;
  int EdgeCount;

  int _LookupVertex(long long v) const;

public:
  //
  // constructor:
  //
  graph();

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const;

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const;

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(long long v);

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(long long from, long long to, double weight);

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(long long from, long long to, double& weight) const;

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<long long> neighbors(long long v) const;

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<long long> getVertices() const;

  //
  // print
  // 
  // Prints the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph G;
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void print(ostream& output) const;

  //
  // buildGraph
  //
  // traverses the nodes and footways to make nodes into
  // vertices and footways into edges on a graph
  //
  void buildGraph(graph& G, Nodes& nodes, Footways& footways);

};
