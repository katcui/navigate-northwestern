/*nodes.h*/

//
// A collection of nodes in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 
// References:
// 
// TinyXML: 
//   files: https://github.com/leethomason/tinyxml2
//   docs:  http://leethomason.github.io/tinyxml2/
// 
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#pragma once

#include <map>

#include "node.h"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;


//
// Keeps track of all the nodes in the map.
//
class Nodes
{
private:
  map<long long, Node> MapNodes;

public:
  //
  // readMapNodes
  //
  // Given an XML document, reads through the document and 
  // stores all the nodes into the given vector. Each node
  // is a point on the map, with a unique id along with 
  // (lat, lon) position. Some nodes are entrances to buildings,
  // which we capture as well.
  //
  void readMapNodes(XMLDocument& xmldoc);

  //
  // sortByID
  //
  // sorts the nodes into ascending order by ID.
  //
  void sortByID();

  //
  // find
  // 
  // Searches the nodes for the one with the matching ID, returning
  // true if found and false if not. If found, the node's Lat, Lon,
  // and IsEntrance data are returned via the reference parameters.
  //
  bool find(long long id, double& lat, double& lon, bool& isEntrance);

  //
  // accessors / getters
  //
  int getNumMapNodes();

  // 
  // allow foreach through the map:
  //
  std::map<long long, Node>::iterator begin();
  std::map<long long, Node>::iterator end();

};

