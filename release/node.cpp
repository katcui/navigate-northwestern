/*node.cpp*/

//
// A node / position in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include "node.h"

using namespace std;


//
// constructor
//
Node::Node(long long id, double lat, double lon, bool entrance)
  : ID(id), Lat(lat), Lon(lon), IsEntrance(entrance)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Lat = lat;
  //this->Lon = lon;
  //this->IsEntrance = entrance;

  Node::Created++;
}

//
// copy constructor:
//
Node::Node(const Node& other)
{
  this->ID = other.ID;
  this->Lat = other.Lat;
  this->Lon = other.Lon;
  this->IsEntrance = other.IsEntrance;

  Node::Copied++;
}

//
// accessors / getters
//
long long Node::getID() {

  Node::CallsToGetID++;

  return this->ID;
}

double Node::getLat() const {
  return this->Lat;
}

double Node::getLon() const {
  return this->Lon;
}

bool Node::getIsEntrance() const {
  return this->IsEntrance;
}

int Node::getCallsToGetID() {
  return Node::CallsToGetID;
}

int Node::getCreated() {
  return Node::Created;
}

int Node::getCopied() {
  return Node::Copied;
}
