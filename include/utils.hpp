#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include "../include/board.hpp"

using namespace std;

// Convert a location to a string
string locationToString(uint8_t location);

uint8_t stringToLocation(string s);

// Convert a move to a string
string moveToString(Move move);

string getFEN(Board& board);

#endif // UTILS_HPP
