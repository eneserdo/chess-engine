#include <iostream>
#include <string>
#include "../include/utils.hpp"

using namespace std;

// Convert a location to a string
string locationToString(uint8_t location)
{
    string locationString = "";
    locationString += (char)('a' + (location % 8));
    locationString += (char)('1' + (location / 8));
    return locationString;
}

uint8_t stringToLocation(string s){
    // TODO
}

// Convert a move to a string
string moveToString(Move move)
{
    string moveString = "";
    moveString += locationToString(move.from);
    moveString += locationToString(move.to);
    return moveString;
}


string getFEN(Board& board)
{
    // TODO
    string fen = "";
    return fen;
}


uint64_t BIT(int x)
{
    return 1ULL << x;
}