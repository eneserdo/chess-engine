#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

enum Piece
{
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// 8 x 8 board:
// #   a  b  c  d  e  f  g  h
// 8  56 57 58 59 60 61 62 63
// 7  48 49 50 51 52 53 54 55
// 6  40 41 42 43 44 45 46 47
// 5  32 33 34 35 36 37 38 39
// 4  24 25 26 27 28 29 30 31
// 3  16 17 18 19 20 21 22 23
// 2   8  9 10 11 12 13 14 15
// 1   0  1  2  3  4  5  6  7


uint8_t getLocation(uint64_t bitBoard);
vector<uint8_t> getLocationList(uint64_t bitBoard);


/// @brief Represents the bit boards for each piece type, 
/// keeps track of castling rights, en passant, half move clock, and full move number.
/// Implementation must be minimal since there will be thousands of instances of this struct. 
struct Board
{
    // Bit boards for each piece type
    // 0 - white, 1 - black
    uint64_t pawns[2], knights[2], bishops[2], rooks[2], queens[2], king[2];
    uint64_t allPieces[2];
    
    // Castling rights
    bool isRookMoved[2][2] = {{false, false}, {false, false}};
    bool isKingMoved[2] = {false, false};

    // TODO: En passant
    // bool enPassant; 
};

void initializeBoard(Board& board);

/// @brief Represents a move, with the starting and ending location, and the piece type
/// @param from (uint8_t) The starting location of the piece
/// @param to (uint8_t) The ending location of the piece
/// @param piece The piece type
struct Move
{ 
    Move(uint8_t from, uint8_t to, Piece piece);
    uint8_t from;
    uint8_t to;
    Piece piece;
    bool operator==(const Move& other) const;
};

vector<uint64_t> getSeparatedBitBoards(uint64_t bitBoard);



#endif // BOARD_HPP