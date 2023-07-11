/*node.h*/

//
// A node / position in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#pragma once

//
// Node:
//
// A node is a point on the map, with a unique ID and the position
// in GPS (lat, lon) terms. A node may also track other information,
// in particular whether this node denotes the entrance to a 
// building.
//
class Node
{
private:
  long long ID;
  double Lat;
  double Lon;
  bool   IsEntrance;

  //
  // These are static / class / singleton variables
  // so that we can collect some statistics on how
  // many times getID( ) is called, how many nodes
  // are created, and how many are copied:
  //
  inline static int CallsToGetID = 0;
  inline static int Created = 0;
  inline static int Copied = 0;

public:
  //
  // constructor
  //
  Node(long long id, double lat, double lon, bool entrance);
  
  //
  // copy constructor:
  //
  Node(const Node& other);

  //
  // accessors / getters
  //
  long long getID();
  double getLat() const;
  double getLon() const;
  bool getIsEntrance() const;

  static int getCallsToGetID();
  static int getCreated();
  static int getCopied();

};
