#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <bitset>
#include <vector>

using namespace std;

// #define BIT(x) (1ULL << x)

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


vector<uint8_t> getLocationList(uint64_t bitboard);


/// @brief Represents the bit boards for each piece type, 
/// keeps track of castling rights, en passant, half move clock, and full move number. 
struct Board
{
    uint64_t whitePawns, whiteKnights, whiteBishops, whiteRooks, whiteQueens, whiteKing;
    uint64_t blackPawns, blackKnights, blackBishops, blackRooks, blackQueens, blackKing;

    uint64_t whitePieces, blackPieces;
    
    bool rookMoved[2][2];
    bool kingMoved[2];
    bool castling[2][2];
    bool enPassant; 
    int halfMoveClock, fullMoveNumber;

    Board();
};

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




#endif // BOARD_HPP