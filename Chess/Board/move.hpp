#pragma once
#include"position.hpp"

class Move{
public:
    Position from;
    Position to;
    Piece* piece; // Pointer to the piece being moved
    Piece* captured_piece; // Pointer to the piece being captured, if any

public:
    Move(Position from, Position to, Piece* piece, Piece* captured_piece = nullptr)
        : from(from), to(to), piece(piece), captured_piece(captured_piece) {}

    Position get_from() const {
        return from;
    }

    Position get_to() const {
        return to;
    }

    Piece* get_piece() const {
        return piece;
    }

    Piece* get_captured_piece() const {
        return captured_piece;
    }
};