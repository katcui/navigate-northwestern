/*main.cpp*/

//
// Program to input Nodes (positions), Buildings and Footways
// from an Open Street Map file.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
#include <limits>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>
#include <utility>

#include "building.h"
#include "buildings.h"
#include "footway.h"
#include "footways.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include "graph.h"
#include "dist.h"

using namespace std;
using namespace tinyxml2;

//
// prioritizes pairs based on values (ascending)
//
class prioritize
{
public: 
   bool operator()(const pair<long long, double>& p1, const pair<long long, double>& p2) const
   {
      if (p1.second > p2.second)
      {
         return true;
      }
      else if (p1.second < p2.second)
      {
         return false;
      }
      else
      {
         return p1.first > p2.first;
      }
   }
};
//
// Dijkstra's algorithm
//
// shortest weighted pathway from start to end
// returns the order of vertices reached by path with pairs
//
vector<long long> Dijkstra(graph& G, long long startV, map<long long, double>& distances, map<long long, long long>& predecessors)
{
  constexpr double INF = numeric_limits<double>::max();
  vector<long long>  visited;
  set<long long> setV;
  //
  // TODO: 
  //
  // NOTE: the value of INF is predefined in "util.h", so use
  // this value to initialize the distances.
  //
  priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> priority;

  // sets distances and predecessors vectors
  for (long long &dp : G.getVertices())
  {
    distances[dp] = INF;
    predecessors[dp] = -1;
  }
  distances[startV] = 0;
  priority.push(make_pair(startV, 0));
  
  // looping through vertices
  while (!priority.empty())
  {
     auto currV = priority.top().first;
     priority.pop();
     
     // not valid
     if (distances[currV] == INF)
     {
        break;
     }
     // continue if vertex was visited already
     else if (setV.count(currV) > 0)
     {
        continue;
     }
     // new vertex
     else 
     {
        visited.push_back(currV);
        setV.insert(currV);
     } // if

     // loop through adjacent vectors of current vertex to find prioritized distance
     for (long long adjV : G.neighbors(currV))
     {
        double weight;

        G.getWeight(currV, adjV, weight);

        if (distances[adjV] > distances[currV] + weight)
        {
          distances[adjV] = distances[currV] + weight;
          predecessors[adjV] = currV;
          priority.push(make_pair(adjV, distances[adjV]));
        }
     } // for
  } // while
  return visited;
} // Dijkstra's

//
// buildGraph
//
// traverses the nodes and footways to make nodes into
// vertices and footways into edges on a graph
//
void buildGraph(graph& G, Nodes& nodes, Footways& footways)
{
  // create each node on graph
  for (auto& node : nodes)
  {
    bool vertex = G.addVertex(node.first);
  }

  // create edges of footways using nodes
  for (auto& fw : footways.MapFootways)
  {
    // traverse node IDs of each footway
    for (size_t i = 0; i < fw.NodeIDs.size() - 1; i++)
    { 
      bool vertex;
      long long from = fw.NodeIDs[i];
      long long to = fw.NodeIDs[i + 1];
      double latFrom, lonFrom, latTo, lonTo;
      double weightFrom, weightTo;
      bool isEntrance;

      // finding nodes to create vertex from latitude and longitude of nodes
      vertex = nodes.find(from, latFrom, lonFrom, isEntrance);
      vertex = nodes.find(to, latTo, lonTo, isEntrance);

      // finds the distance between the found vertices
      // adds the edge from vertex1 to vertex2
      weightFrom = distBetween2Points(latFrom, lonFrom, latTo, lonTo);
      vertex = G.addEdge(from, to, weightFrom);

      // repeat for to
      weightTo = distBetween2Points(latTo, lonTo, latFrom, lonFrom);
      vertex = G.addEdge(to, from, weightTo);
    } //for
  } //for
} //buildGraph

//
// sanityCheck
//
// Returns the edges from a footway to ensure graph is building correctly
//
void sanityCheck(graph& g, Footway& fw)
{
  cout << "Graph check of Footway ID " << fw.ID << endl;

  // find edges for corresponding footway and output
  for (size_t i = 0; i < fw.NodeIDs.size() - 1; i++)
  {
    long long from = fw.NodeIDs[i];
    long long to = fw.NodeIDs[i + 1];
    double distance;
    bool vertex;

    // from to
    vertex = g.getWeight(from, to, distance);
    cout << "  Edge: (" << from << ", " << to << ", " << distance << ")" << endl;
    
    // to from
    vertex = g.getWeight(to, from, distance);
    cout << "  Edge: (" << to << ", " << from << ", " << distance << ")" << endl;
  } //for
}// sanityCheck

// loops through the footways for the sanity check above
// specific ID of 986532630
void loopSanity(graph& g, Footways& footways)
{
  for (Footway& fw: footways.MapFootways)
  {
    if (fw.ID == 986532630)
    {
      sanityCheck(g, fw);
      break;
    }
  }//for
} //loopSanity

//
// minDist
//
// Finds the closest footway node to a lat,lon pair and gives the nodeid
//
long long minDist(Footways& footways, Building& building, Nodes& nodes, double lat1, double lon1)
{
  constexpr double INF = numeric_limits<double>::max();
  double minD = INF;
  long long minFootway = 0;
  long long minNode = 0;

  // loops through the footways
  for (Footway& fw : footways.MapFootways)
  {
    // loops through the nodes
    for (long long nodeid : fw.NodeIDs)
    {
      double lat2, lon2;
      bool isEntrance;

      bool found = nodes.find(nodeid, lat2, lon2, isEntrance);
      double dist = distBetween2Points(lat1, lon1, lat2, lon2);

      // sets min distance, footwayid, and nodeid
      if (dist < minD) 
      {
        minD = dist;
        minFootway = fw.ID;
        minNode = nodeid;
      }
    }
  }

  // output data
  cout << "  Closest footway ID " << minFootway << ", node ID " << minNode << ", distance " << minD << endl;

  return minNode;
}

//
// navigate
//
// user navigating between 2 buildings
//
void navigate(graph G, Buildings& buildings, Nodes& nodes, Footways& footways)
{
  constexpr double INF = numeric_limits<double>::max();
  string start, end;

  Building startB(0, "", "");
  Building endB(0, "", "");

  cout << "Enter start building name (partial or complete)> " << endl;

  // get the building user is at
  getline(cin, start);

  // loop through the buildings
  for (Building& B : buildings.MapBuildings)
  {
    if (B.Name.find(start) != string::npos) //desired building at
    { 
      startB = B;
      break;
    }
  }// for

  // if the building is not found, output this
  if (startB.ID == 0)  
  {
    cout << "**Start building not found" << endl;
    return;
  }

  cout << "  Name: " << startB.Name << endl;

  double lat1 = startB.getLocation(nodes).first;
  double lon1 = startB.getLocation(nodes).second;
  cout << "  Approximate location: (" << lat1 << ", " << lon1 << ")" << endl;

  // auto pair = startB.getLocation(nodes);
  // cout << "  Approximate location: (" << pair.first << ", " << pair.second << ")" << endl;

  long long minStartID;

  minStartID = minDist(footways, startB, nodes, lat1, lon1);

  cout << "Enter destination building name (partial or complete)> " << endl;

  // get the building user wants to travel to
  getline(cin, end);

  for (Building& B : buildings.MapBuildings)
  {
    if (B.Name.find(end) != string::npos) 
    { 
      endB = B;
      break;
    }
  }//for

  if (endB.ID == 0) 
  {
    cout << "**Destination building not found" << endl;
    return;
  }

  cout << "  Name: " << endB.Name << endl;

  double lat2 = endB.getLocation(nodes).first;
  double lon2 = endB.getLocation(nodes).second;
  cout << "  Approximate location: (" << lat2 << ", " << lon2 << ")" << endl;

  long long minEndID; 

  minEndID = minDist(footways, endB, nodes, lat2, lon2);

  // with the endpoints, use Dikstras
  cout << "Shortest weighted path:" << endl;

  long long startPoint = minStartID;
  map<long long, double> distanceAcc;
  map<long long, long long> visitedPoints;

  auto visited = Dijkstra(G, minStartID, distanceAcc, visitedPoints);
  double distLeft = distanceAcc[minEndID];

  // not valid endpoint
  if (distLeft == INF)
  {
    cout << "**Sorry, destination unreachable" << endl;
  }
  else // valid, continue
  {
    cout << "  # nodes visited: " << visited.size() << endl;
    cout << "  Distance: " << distanceAcc[minEndID] << " miles" << endl;
    cout << "  Path: ";

    stack<long long> path;
    auto vert = minEndID;

    path.push(vert);

    // exists, lood through visited p;oints
    // push into path
    while (visitedPoints[vert] != -1)
    {
      path.push(visitedPoints[vert]);
      vert = visitedPoints[vert];
    } //while

    // loop through path stack until empty
    while (!path.empty())
    {
      vert = path.top();
      path.pop(); // empties path

      cout << vert;

      // output clarity, last element does not have "->"
      if (path.size() > 0)
        cout << "->";
    } //while
    cout << endl;
  }//if
}// navigate

//
// main
//
int main()
{
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  Footways footways;
  graph G;
  
  cout << setprecision(12);
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // 1. load XML-based map file 
  //
  if (!osmLoadMapFile(filename, xmldoc))
  {
    // failed, error message already output
    return 0;
  }
  
  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // NOTE: let's sort so we can use binary search when we need 
  // to lookup nodes.
  //
  nodes.sortByID();

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // 4. read the footways, which are the walking paths:
  //
  footways.readMapFootways(xmldoc);
  buildGraph(G, nodes, footways);

  //
  // 5. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of footways: " << footways.getNumMapFootways() << endl;
  cout << "# of graph vertices: " << G.NumVertices() << endl;
  cout << "# of graph edges: " << G.NumEdges() << endl;

  //
  // now let the user for search for 1 or more buildings:
  //
  while (true)
  {
    string name;

    cout << endl;
    cout << "Enter building name, * to list, @ to navigate, or $ to end> " << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    }
    else if (name == "*") {
      buildings.print();
    }
    else if (name == "!") { // sanity check
      loopSanity(G, footways);
    }
    else if (name == "@") {
      navigate(G, buildings, nodes, footways);
    }
    else {
      buildings.findAndPrint(name, nodes, footways);
    }

  }//while

  //
  // done:
  //
  cout << endl;
  cout << "** Done  **" << endl;
  cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  cout << "# of Nodes created: " << Node::getCreated() << endl;
  cout << "# of Nodes copied: " << Node::getCopied() << endl;
  cout << endl;

  return 0;
}
