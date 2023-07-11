/*osm.cpp*/

//
// Functions for working with an Open Street Map file.
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

#include <iostream>
#include <string>
#include <cassert>

#include "osm.h"

using namespace std;
using namespace tinyxml2;


//
// osmLoadMapFile
// 
// Given the filename for an XML doc, tries to open and load
// that file into the given xmldoc variable (which is passed
// by reference). Returns true if successful, false if the 
// file could not be opened OR the file does not contain 
// an Open Street Map document.
//
bool osmLoadMapFile(string filename, XMLDocument& xmldoc)
{
  //
  // load the XML document:
  //
  xmldoc.LoadFile(filename.c_str());

  if (xmldoc.ErrorID() != 0)  // failed:
  {
    cout << "**ERROR: unable to open XML file '" << filename << "'." << endl;
    return false;
  }

  //
  // top-level element should be "osm" if the file is a valid open 
  // street map:
  //
  XMLElement* osm = xmldoc.FirstChildElement("osm");

  if (osm == nullptr)
  {
    cout << "**ERROR: unable to find top-level 'osm' XML element." << endl;
    cout << "**ERROR: this file is probably not an Open Street Map." << endl;
    return false;
  }

  //
  // success:
  //
  return true;
}


//
// osmContainsKeyValue
//
// Given a pointer to an XML Element, searches through all 
// the tags associated with this element looking for the 
// given (key, value) pair.  For example, the call
//
//   containsKeyValue(e, "entrance", "yes")
//
// will return true if it comes across the tag
//
//   <tag k="entrance" v="yes"/>
//
bool osmContainsKeyValue(XMLElement* e, string key, string value)
{
  XMLElement* tag = e->FirstChildElement("tag");

  while (tag != nullptr)
  {
    const XMLAttribute* keyAttribute = tag->FindAttribute("k");
    const XMLAttribute* valueAttribute = tag->FindAttribute("v");

    if (keyAttribute != nullptr && valueAttribute != nullptr)
    {
      string elemkey(keyAttribute->Value());
      string elemvalue(valueAttribute->Value());

      if (elemkey == key && elemvalue == value)  // found it:
      {
        return true;
      }
    }

    //
    // not a match, try the next tag:
    //
    tag = tag->NextSiblingElement("tag");
  }

  //
  // if get here, not found:
  //
  return false;
}


//
// osmGetKeyValue
//
// Given a pointer to an XML Element, searches through all 
// the tags associated with this element looking for the 
// given key. If found, returns the associated value. For
// example, given the call
//
//   getKeyValue(e, "entrance")
//
// will return "yes" if it comes across the tag
//
//   <tag k="entrance" v="yes"/>
// 
// If the key is not found, the empty string "" is returned.
//
string osmGetKeyValue(XMLElement* e, string key)
{
  XMLElement* tag = e->FirstChildElement("tag");

  while (tag != nullptr)
  {
    const XMLAttribute* keyAttribute = tag->FindAttribute("k");
    const XMLAttribute* valueAttribute = tag->FindAttribute("v");

    if (keyAttribute != nullptr && valueAttribute != nullptr)
    {
      string elemkey(keyAttribute->Value());
      
      if (elemkey == key)  // found it:
      {
        string elemvalue(valueAttribute->Value());

        return elemvalue;
      }
    }

    //
    // not a match, try the next tag:
    //
    tag = tag->NextSiblingElement("tag");
  }

  //
  // if get here, not found:
  //
  return "";
}
