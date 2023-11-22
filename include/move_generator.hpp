#ifndef MOVE_GENERATOR_HPP
#define MOVE_GENERATOR_HPP

#include <iostream>
#include <vector>
#include <unordered_map>

#include "../include/board.hpp"
using namespace std;

typedef vector<vector<uint64_t>> VVB;


// Generate moves for each piece type (pseudo-legal moves, only considers if the piece is on board)
// These functions are used to generate the move look up table, so they will be called only once!
VVB _generateMovesRook(uint64_t rooks);
VVB _generateMoveKing(uint64_t king);
VVB _generateMoveKnight(uint64_t knight);
VVB _generateMovePawn(uint64_t pawn);
VVB _generateMoveBishop(uint64_t bishop);
VVB _generateMoveQueen(uint64_t queen);


// Generate all pseudo-legal moves
void generateMoves(Board &board, vector<Move> &moves, bool isWhiteTurn);


class MoveLookUpTable
{
private:
    // TODO: maybe declare it as static const
    unordered_map<uint64_t, VVB> moveTableRook, moveTableKing, moveTableKnight, moveTablePawn, moveTableBishop, moveTableQueen;

public:
    MoveLookUpTable();

    // This will create a copy of VVB, which is not efficient
    // TODO: check if the bitBoard has only one bit set 
    VVB getPossibleMoves(Piece piece, uint64_t bitBoard);
};

#endif // MOVE_GENERATOR_HPP