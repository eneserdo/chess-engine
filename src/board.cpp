#include "../include/board.hpp"
// #include "../include/utils.hpp"  // Error: circular dependency
using namespace std;

#define BIT(x) (1ULL << x)


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


uint8_t getLocation(uint64_t bitBoard)
{
    for (int i = 0; i < 64; i++)
    {
        if (bitBoard & BIT(i))
        {
            return i;
        }
    }
    throw "getLocation: bitBoard is empty";
}

vector<uint8_t> getLocationList(uint64_t bitboard)
{
    // CHECKME: returning a local variable might cause unnecessary copying
    vector<uint8_t> locationList;
    for (int i = 0; i < 64; i++)
    {
        if (bitboard & BIT(i))
        {
            locationList.push_back(i);
        }
    }
    return locationList;
}


void initializeBoard(Board &board)
{   
    // White pieces
    board.pawns[0] = BIT(8) | BIT(9) | BIT(10) | BIT(11) | BIT(12) | BIT(13) | BIT(14) | BIT(15);
    board.knights[0] = BIT(1) | BIT(6);
    board.bishops[0] = BIT(2) | BIT(5);
    board.rooks[0] = BIT(0) | BIT(7);
    board.queens[0] = BIT(3);
    board.king[0] = BIT(4);

    // Black pieces
    board.pawns[1] = BIT(48) | BIT(49) | BIT(50) | BIT(51) | BIT(52) | BIT(53) | BIT(54) | BIT(55);
    board.knights[1] = BIT(57) | BIT(62);
    board.bishops[1] = BIT(58) | BIT(61);
    board.rooks[1] = BIT(56) | BIT(63);
    board.queens[1] = BIT(59);
    board.king[1] = BIT(60);

    board.allPieces[0] = board.pawns[0] | board.knights[0] | board.bishops[0] | board.rooks[0] | board.queens[0] | board.king[0];
    board.allPieces[1] = board.pawns[1] | board.knights[1] | board.bishops[1] | board.rooks[1] | board.queens[1] | board.king[1];

    // board.isRookMoved, board.isKingMoved are initialized to false by default
};

vector<uint64_t> getSeparatedBitBoards(uint64_t bitBoard)
{
    vector<uint64_t> bitBoards;
    for (int i = 0; i < 64; i++)
    {
        if (bitBoard & BIT(i))
        {
            bitBoards.push_back(BIT(i));
        }
    }
    return bitBoards;
}
Move::Move(uint8_t from, uint8_t to, Piece piece) : from(from), to(to), piece(piece) {}


bool Move::operator==(const Move &other) const
{
    return (from == other.from && to == other.to && piece == other.piece);
}
