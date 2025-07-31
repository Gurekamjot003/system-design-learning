#pragma once
#include "piece.hpp"

class Queen : public Piece {
public:
    Queen(Color color) : Piece(color, PieceType::QUEEN) {}

    vector<Position> get_possible_moves(Position pos, Board* board) override;
    string get_symbol() override {
        return "Q";
    }
};