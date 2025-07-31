#pragma once
#include "piece.hpp"

class Rook: public Piece {
public:
    Rook(Color color) : Piece(color, PieceType::ROOK) {}

    vector<Position> get_possible_moves(Position pos, Board* board) override;
    string get_symbol() override {
        return "R";
    }

};