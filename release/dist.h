/*dist.h*/

//
// Computes the distance between 2 positions, given in
// (latitude, longitude) coordinates.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>
#include <cmath>

using namespace std;

//
// DistBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2). Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west. Example: Chicago is (41.88, -87.63).
//
// NOTE: you may get slightly different results depending on which 
// (lat, long) pair is passed as the first parameter.
// 
double distBetween2Points(double lat1, double long1, double lat2, double long2);
