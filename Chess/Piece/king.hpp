#pragma once
#include "piece.hpp"

class King : public Piece {
public:
    King(Color color) : Piece(color, PieceType::KING) {}

    vector<Position> get_possible_moves(Position pos, Board* board) override;
    string get_symbol() override {
        return "K";
    }
};