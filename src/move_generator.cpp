#include "../include/move_generator.hpp"
#include "../include/utils.hpp"

bool generateMoveKing(uint64_t king, Board &board, vector<Move> &moves, bool isWhiteTurn)
{
    auto L = getLocationList(king);

    for (int i : {-1, 0, 1})
    {
        for (int j : {-1, 0, 1})
        {
            if (i == 0 && j == 0)
                continue;

            moves.push_back(Move(L[0], L[0] + i * 8 + j, KING));
        }
    }
}

bool generateMoveKnight(uint64_t knight, Board &board, vector<Move> &moves, bool isWhiteTurn)
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
bool generateMoves(Board &board, bool isBlackTurn)
{
    // Possible moves for each piece type. It can be changed to vector of boards
    vector<Move> moves;

    // generateMoveKing(board.king[isBlackTurn], board, moves, isBlackTurn);
    // generateMoveKnight(board.knights[isBlackTurn], board, moves, isBlackTurn);
    // generateMovesRook(board.rooks[isBlackTurn], board, moves, isBlackTurn);
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

MoveLookUpTable::MoveLookUpTable()
{
    // Initialize move table for rook
    for (int i = 0; i < 64; i++)
    {
        uint64_t piece = (1ULL << i);

        this->moveTableRook[piece] = _generateMovesRook(piece);
        this->moveTableKing[piece] = _generateMoveKing(piece);
        this->moveTableKnight[piece] = _generateMoveKnight(piece);
        this->moveTablePawn[piece] = _generateMovePawn(piece);
        this->moveTableBishop[piece] = _generateMoveBishop(piece);
        this->moveTableQueen[piece] = _generateMoveQueen(piece);

    }

}

VVB MoveLookUpTable::getPossibleMoves(Piece piece, uint64_t bitBoard)
{
    {
        switch (piece)
        {
        case ROOK:
            return moveTableRook[bitBoard];
            break;
        case KING:
            return moveTableKing[bitBoard];
            break;
        case KNIGHT:
            return moveTableKnight[bitBoard];
            break;
        case PAWN:
            return moveTablePawn[bitBoard];
            break;
        case BISHOP:
            return moveTableBishop[bitBoard];
            break;
        case QUEEN:
            return moveTableQueen[bitBoard];
            break;

        default:
            throw "Invalid piece type";
            break;
        }
    }
}

VVB _generateMovesRook(uint64_t rooks)
{
    VVB bitBoardList;

    uint8_t L = getLocation(rooks);

    uint8_t x = L % 8;
    uint8_t y = L / 8;
    uint8_t direction = 0;

    // In the same row
    if (x != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = x + 1; i < 8; i++)
            bitBoardList[direction].push_back(BIT(i + y * 8));

        direction++;
    }

    if (x != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = x - 1; i < 8; i--)
            bitBoardList[direction].push_back(BIT(i + y * 8));

        direction++;
    }

    if (y != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = y + 1; i < 8; i++)
            bitBoardList[direction].push_back(BIT(x + i * 8));

        direction++;
    }

    if (y != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = y - 1; i < 8; i--)
            bitBoardList[direction].push_back(BIT(x + i * 8));

        direction++;
    }

    return bitBoardList;
}

VVB _generateMoveKing(uint64_t king)
{
    VVB bitBoardList;

    uint8_t L = getLocation(king);
    uint8_t x = L % 8;
    uint8_t y = L / 8;

    bitBoardList.push_back(vector<uint64_t>());

    for (int i : {-1, 0, 1})
    {
        for (int j : {-1, 0, 1})
        {
            if (i == 0 && j == 0)
                continue;

            // check if the move is on the board
            if (x + i < 0 || x + i > 7 || y + j < 0 || y + j > 7)
                continue;

            bitBoardList[0].push_back(BIT((x + i) + (y + j) * 8));
        }
    }
    
    return bitBoardList;
}

VVB _generateMoveKnight(uint64_t knight)
{
    VVB bitBoardList;

    uint8_t L = getLocation(knight);

    uint8_t x = L % 8;
    uint8_t y = L / 8;

    bitBoardList.push_back(vector<uint64_t>());

    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            // (-2, 1), (-2, -1), (2, 1), (2, -1), (1, 2), (-1, 2), (1, -2), (-1, -2)
            if (i == 0 || j == 0 || i == j || i == -j)
                continue;

            // check if the move is on the board
            if (x + i < 0 || x + i > 7 || y + j < 0 || y + j > 7)
                continue;

            bitBoardList[0].push_back(BIT((x + i) + (y + j) * 8));
        }
    }

    return bitBoardList;
}

VVB _generateMoveBishop(uint64_t bishop)
{
    VVB bitBoardList;

    uint8_t L = getLocation(bishop);

    uint8_t x = L % 8;
    uint8_t y = L / 8;
    uint8_t direction = 0;

    // north east
    if (x != 7 && y != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x + i > 7 || y + i > 7)
                break;

            bitBoardList[direction].push_back(BIT((x + i) + (y + i) * 8));
        }

        direction++;
    }

    // north west
    if (x != 0 && y != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x - i < 0 || y + i > 7)
                break;

            bitBoardList[direction].push_back(BIT((x - i) + (y + i) * 8));
        }

        direction++;
    }

    // south east
    if (x != 7 && y != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x + i > 7 || y - i < 0)
                break;

            bitBoardList[direction].push_back(BIT((x + i) + (y - i) * 8));
        }

        direction++;
    }

    // south west
    if (x != 0 && y != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x - i < 0 || y - i < 0)
                break;

            bitBoardList[direction].push_back(BIT((x - i) + (y - i) * 8));
        }

        direction++;
    }

    return bitBoardList;
}


VVB _generateMoveQueen(uint64_t queen)
{
    VVB bitBoardList;

    uint8_t L = getLocation(queen);

    uint8_t x = L % 8;
    uint8_t y = L / 8;
    uint8_t direction = 0;

    // north east
    if (x != 7 && y != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x + i > 7 || y + i > 7)
                break;

            bitBoardList[direction].push_back(BIT((x + i) + (y + i) * 8));
        }

        direction++;
    }

    // north west
    if (x != 0 && y != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x - i < 0 || y + i > 7)
                break;

            bitBoardList[direction].push_back(BIT((x - i) + (y + i) * 8));
        }

        direction++;
    }

    // south east
    if (x != 7 && y != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x + i > 7 || y - i < 0)
                break;

            bitBoardList[direction].push_back(BIT((x + i) + (y - i) * 8));
        }

        direction++;
    }

    // south west
    if (x != 0 && y != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = 1; i < 8; i++)
        {
            if (x - i < 0 || y - i < 0)
                break;

            bitBoardList[direction].push_back(BIT((x - i) + (y - i) * 8));
        }

        direction++;
    }

    // In the same row
    if (x != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = x + 1; i < 8; i++)
            bitBoardList[direction].push_back(BIT(i + y * 8));

        direction++;
    }

    if (x != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = x - 1; i < 8; i--)
            bitBoardList[direction].push_back(BIT(i + y * 8));

        direction++;
    }

    if (y != 0)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = y + 1; i < 8; i++)
            bitBoardList[direction].push_back(BIT(x + i * 8));

        direction++;
    }

    if (y != 7)
    {
        bitBoardList.push_back(vector<uint64_t>());

        for (size_t i = y - 1; i < 8; i--)
            bitBoardList[direction].push_back(BIT(x + i * 8));

        direction++;
    }

    return bitBoardList;
}

VVB _generateMovePawn(uint64_t pawn)
{
    // TODO: En passant

    // FIXME: maybe create func for white and black pawns separately

    VVB bitBoardList;

    uint8_t L = getLocation(pawn);

    uint8_t x = L % 8;
    uint8_t y = L / 8;

    bitBoardList.push_back(vector<uint64_t>());

    if (y != 7)
    {
        bitBoardList[0].push_back(BIT(x + (y + 1) * 8));
    }

    if (y == 1)
    {
        bitBoardList[0].push_back(BIT(x + (y + 2) * 8));
    }

    return bitBoardList;
}