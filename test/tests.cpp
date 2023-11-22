
#include <iostream>
#include <algorithm>
#include <gtest/gtest.h>

#include "../include/move_generator.hpp"
#include "../include/board.hpp"
#include "../include/utils.hpp"

using namespace std;

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

MoveLookUpTable moveLookUpTable;

// Helper function to sort moves
void sortMoves(vector<Move> &moves)
{
    sort(moves.begin(), moves.end(), [](const Move &a, const Move &b)
         { 
        if(a.from != b.from)
            return a.from < b.from;
        else
            return a.to < b.to; });
}

vector<uint64_t> flattenVVB(vector<vector<uint64_t>> &v)
{
    vector<uint64_t> flattened;
    for (auto &row : v)
    {
        flattened.insert(flattened.end(), row.begin(), row.end());
    }
    return flattened;
}

// Knight move tests
// TEST(GenerateMoveKnightTest, t1)
// {
//     uint64_t knight = (1ULL << 1); // Knight on b1

//     vector<Move> moves;
//     generateMoveKnight(knight, moves);
//     vector<Move> expected_moves = {
//         Move(1, 16, KNIGHT),
//         Move(1, 18, KNIGHT),
//         Move(1, 11, KNIGHT)};

//     // sort(moves.begin(), moves.end(), [](const Move &a, const Move &b) { return a.to < b.to; });
//     // sort(expected_moves.begin(), expected_moves.end(), [](const Move &a, const Move &b) { return a.to < b.to; });
//     sortMoves(moves);
//     sortMoves(expected_moves);

//     for (int i = 0; i < moves.size(); i++)
//     {
//         EXPECT_EQ(moves[i].from, expected_moves[i].from);
//         EXPECT_EQ(moves[i].to, expected_moves[i].to);
//         EXPECT_EQ(moves[i].piece, expected_moves[i].piece);
//     }

// }

// Rook move tests
TEST(GenerateMoveRookTest, test1)
{
    uint64_t rook = (1ULL << 1); // Knight on b1

    VVB moves_ = moveLookUpTable.getPossibleMoves(ROOK, rook);
    
    vector<uint64_t> moves = flattenVVB(moves_);

    vector<uint64_t> expected_moves = {
        BIT(0), BIT(2), BIT(3), BIT(4), BIT(5), BIT(6), BIT(7),
        BIT(9), BIT(17), BIT(25), BIT(33), BIT(41), BIT(49), BIT(57)};

    sort(moves.begin(), moves.end());
    sort(expected_moves.begin(), expected_moves.end());

    EXPECT_EQ(moves.size(), expected_moves.size());

    for (int i = 0; i < moves.size(); i++)
    {
        EXPECT_EQ(moves[i], expected_moves[i]);
    }
}

TEST(GenerateMoveRookTest, test2)
{
    uint64_t rook = (1ULL << 56); // Knight on b1

    VVB moves_ = moveLookUpTable.getPossibleMoves(ROOK, rook);
    
    vector<uint64_t> moves = flattenVVB(moves_);

    vector<uint64_t> expected_moves = {
        BIT(57), BIT(58), BIT(59), BIT(60), BIT(61), BIT(62), BIT(63),
        BIT(48), BIT(40), BIT(32), BIT(24), BIT(16), BIT(8), BIT(0)};

    sort(moves.begin(), moves.end());
    sort(expected_moves.begin(), expected_moves.end());

    EXPECT_EQ(moves.size(), expected_moves.size());

    for (int i = 0; i < moves.size(); i++)
    {
        EXPECT_EQ(moves[i], expected_moves[i]);
    }
}

TEST(GenerateMoveKnightTest, test1)
{
    uint64_t rook = (1ULL << 1); // Knight on b1

    VVB moves_ = moveLookUpTable.getPossibleMoves(KNIGHT, rook);
    
    vector<uint64_t> moves = flattenVVB(moves_);

    vector<uint64_t> expected_moves = {BIT(16), BIT(18), BIT(11)};

    sort(moves.begin(), moves.end());
    sort(expected_moves.begin(), expected_moves.end());

    EXPECT_EQ(moves.size(), expected_moves.size());

    for (int i = 0; i < moves.size(); i++)
    {
        EXPECT_EQ(moves[i], expected_moves[i]);
    }
}

TEST(GenerateMoveKnightTest, test2)
{
    uint64_t rook = (1ULL << 45); // Knight on b1

    VVB moves_ = moveLookUpTable.getPossibleMoves(KNIGHT, rook);
    
    vector<uint64_t> moves = flattenVVB(moves_);

    vector<uint64_t> expected_moves = {BIT(51), BIT(60), BIT(62), BIT(55), BIT(39), BIT(30), BIT(28), BIT(35)};

    sort(moves.begin(), moves.end());
    sort(expected_moves.begin(), expected_moves.end());

    EXPECT_EQ(moves.size(), expected_moves.size());

    for (int i = 0; i < moves.size(); i++)
    {
        EXPECT_EQ(moves[i], expected_moves[i]);
    }
}



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}