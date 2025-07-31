#pragma once
#include "piece.hpp"

class Pawn: public Piece {
public:
    Pawn(Color color) : Piece(color, PieceType::PAWN) {}

    vector<Position> get_possible_moves(Position pos, Board* board) override;
    string get_symbol() override {
        return "P";
    }

};