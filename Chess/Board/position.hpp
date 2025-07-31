#pragma once
#include<bits/stdc++.h>
using namespace std;

class Board;
class Piece;
class Match;
class User;

class Position{
    int row, col;
    
public:
    Position(int r, int c) : row(r), col(c) {}

    int get_row() const {
        return row;
    }

    int get_col() const {
        return col;
    }

    bool is_valid(){
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }

    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }

    bool operator<=(const Position& other) const {
        return row < other.row || (row == other.row && col <= other.col);
    }

    string to_string() const {
        return "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
    }

    string to_algebraic_notation() const {
        char file = 'a' + col; // Convert column index to file letter
        int rank = 8 - row; // Convert row index to rank number
        return string(1, file) + std::to_string(rank);
    }
};