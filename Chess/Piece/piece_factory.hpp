#pragma once
#include "piece.hpp"
#include "pawn.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "rook.hpp"
#include "queen.hpp"
#include "king.hpp"


class PieceFactory {
public:
    static Piece* create_piece(Color color, PieceType type) {
        switch (type) {
            case PieceType::PAWN:
                return new Pawn(color);
            case PieceType::ROOK:
                return new Rook(color);
            case PieceType::KNIGHT:
                return new Knight(color);
            case PieceType::BISHOP:
                return new Bishop(color);
            case PieceType::QUEEN:
                return new Queen(color);
            case PieceType::KING:
                return new King(color);
            default:
                return nullptr;
        }
    }
};