#pragma once
#include "piece.hpp"

class Knight: public Piece {
public:
    Knight(Color color) : Piece(color, PieceType::KNIGHT) {}

    vector<Position> get_possible_moves(Position pos, Board* board) override;
    string get_symbol() override {
        return "N";
    }

};