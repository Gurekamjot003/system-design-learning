#pragma once
#include "color.hpp"
#include "piece_type.hpp"
#include "../board/position.hpp"

class Piece{
    Color color;
    PieceType type;
    bool has_moved;

public:
    Piece(Color c, PieceType t) : color(c), type(t), has_moved(false){}

    Color get_color() const {
        return color;
    }

    PieceType get_type() const {
        return type;
    }

    bool has_moved_once() const {
        return has_moved;
    }

    void mark_as_moved() {
        has_moved = true;
    }

    virtual vector<Position> get_possible_moves(Position pos, Board* board) = 0;
    virtual string get_symbol() = 0;

    string to_string() {
        return "Piece(" + get_symbol() + ", " + (color == Color::WHITE ? "White" : "Black") + ")";
    }

};