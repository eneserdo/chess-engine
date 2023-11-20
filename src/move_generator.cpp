#include "../include/move_generator.hpp"

void generateMovesRook(uint64_t rooks, Board &board, vector<Move> &moves)
{
    vector<uint8_t> L = getLocationList(rooks);

    // Possible moves
    // vector<Move> moves;
    uint8_t x, y;

    for (int i = 0; i < L.size(); i++)
    {
        // In the same row
        for (size_t i = 1; i < 8; i++)
        {
            moves.push_back(Move(L[i], (L[i] + i * 8) % 8, ROOK));
        }

        x = L[i] % 8;
        y = L[i] / 8;

        for (size_t i = 1; i < 8; i++)
        {
            moves.push_back(Move(L[i], (x + i) % 8 + y * 8, ROOK));
        }
    }
}

void generateMoveKing(uint64_t king, Board &board, vector<Move> &moves)
{
    auto L = getLocationList(king);

    // Possible moves
    // vector<Move> moves;

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
                continue;

            moves.push_back(Move(L[0], L[0] + i * 8 + j, KING));
        }
    }
}

void generateMoveKnight(uint64_t knight, Board &board, vector<Move> &moves)
{
    auto L = getLocationList(knight);

    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            if (i == 0 || j == 0 || i == j || i == -j)
                continue;

            // (-2, 1), (-2, -1), (2, 1), (2, -1), (1, 2), (-1, 2), (1, -2), (-1, -2)

            // check if the move is on the board
            if ((int16_t)L[0] + i * 8 + j < 0 || (int16_t)L[0] + i * 8 + j > 63)
                continue;

            moves.push_back(Move(L[0], L[0] + i * 8 + j, KNIGHT));
        }
    }
}

/// @brief Generate all possible pseudo-legal moves for a given board, and store them in a vector
void generateMoves(Board &board, vector<Move> &moves, bool isWhiteTurn)
{

    if (isWhiteTurn)
    {
        generateMoveKing(board.whiteKing, moves);
        generateMoveKnight(board.whiteKnights, moves);
        generateMovesRook(board.whiteRooks, moves);
    }
    else
    {
        generateMoveKing(board.blackKing, moves);
        generateMoveKnight(board.blackKnights, moves);
        generateMovesRook(board.blackRooks, moves);
    }
}

/// @brief Filter out illegal moves:
///         - Moves that leave the king in check
///         - Moves that capture the king
///         - Moves that are blocked by other pieces
void filterMoves(Board &board, vector<Move> &moves, bool isWhiteTurn)
{
    for (const Move &m : moves)
    {
        if (m.piece == KNIGHT)
        {
            // Check only "to" has opponent's piece
        }
        else if (m.piece == KING)
        {
            // Check if "to" is in opponent's attack range
        }
        else
        {
            // Check if there is a piece between "from" and "to"
        }
    }
}
