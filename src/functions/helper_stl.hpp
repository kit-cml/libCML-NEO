#ifndef HELPER_STL_HPP
#define HELPER_STL_HPP

#include <vector>
#include <string>

// helper_stl.hpp
// Collection of helper functions
// that related to STL modifications/manipulations.
// 
// Dunno about STL? Hit the books!!!
// In short, STL is a collection of things about
// data structures.
// Vectors, Map, Array (the class), are included in this area.
//
// Reminder:
// Never ever return data structures in the functions.
// Let the data structures as the call-by-references to avoid
// copying.

using std::string;
using std::vector;

// Function to split a string by a given delimiter
// and save it into a vector.
void split_string( const string &str, char delimiter, vector<string> &result );

#endif