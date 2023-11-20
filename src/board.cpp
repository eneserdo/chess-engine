#include "../include/board.hpp"

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


Board::Board()
{
    whitePawns = BIT(8) | BIT(9) | BIT(10) | BIT(11) | BIT(12) | BIT(13) | BIT(14) | BIT(15);
    whiteKnights = BIT(1) | BIT(6);
    whiteBishops = BIT(2) | BIT(5);
    whiteRooks = BIT(0) | BIT(7);
    whiteQueens = BIT(3);
    whiteKing = BIT(4);

    blackPawns = BIT(48) | BIT(49) | BIT(50) | BIT(51) | BIT(52) | BIT(53) | BIT(54) | BIT(55);
    blackKnights = BIT(57) | BIT(62);
    blackBishops = BIT(58) | BIT(61);
    blackRooks = BIT(56) | BIT(63);
    blackQueens = BIT(59);
    blackKing = BIT(60);

    whitePieces = whitePawns | whiteKnights | whiteBishops | whiteRooks | whiteQueens | whiteKing;
    blackPieces = blackPawns | blackKnights | blackBishops | blackRooks | blackQueens | blackKing;

    // rookMoved = false;
    // kingMoved = false;
    // castling = {false};
    enPassant = 0;
    halfMoveClock = 0;
    fullMoveNumber = 0;
};


Move::Move(uint8_t from, uint8_t to, Piece piece) : from(from), to(to), piece(piece) {}


bool Move::operator==(const Move &other) const
{
    return (from == other.from && to == other.to && piece == other.piece);
}
