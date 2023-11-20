#ifndef MOVE_GENERATOR_HPP
#define MOVE_GENERATOR_HPP

#include <iostream>
#include <vector>

#include "../include/board.hpp"
using namespace std;

// TODO: only generate legal moves instead of pseudo-legal moves
// Generate moves for each piece type (pseudo-legal moves)
void generateMovesRook(uint64_t rooks, Board& board, vector<Move>& moves);
void generateMoveKing(uint64_t king, Board& board, vector<Move>& moves);
void generateMoveKnight(uint64_t knight, Board& board, vector<Move>& moves);

// Generate all pseudo-legal moves
void generateMoves(Board& board, vector<Move>& moves, bool isWhiteTurn);

// Filter out illegal moves
void filterMoves(Board& board, vector<Move>& moves, bool isWhiteTurn);

void isKingInCheck(Board& board, bool isWhiteTurn);


#endif // MOVE_GENERATOR_HPP