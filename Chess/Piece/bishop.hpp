#pragma once
#include "piece.hpp"

class Bishop: public Piece {
public:
    Bishop(Color color) : Piece(color, PieceType::BISHOP) {}

    vector<Position> get_possible_moves(Position pos, Board* board) override;
    string get_symbol() override {
        return "B";
    }

};