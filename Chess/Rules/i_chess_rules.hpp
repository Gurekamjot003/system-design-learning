#pragma once
#include "../Board/board.hpp"
#include "../Board/move.hpp"

class IChessRules{
    
public:
    virtual bool is_valid_move(const Move& move, Board* board) = 0;
    virtual bool is_in_check(Color king_color, Board* board) = 0;
    virtual bool is_check_mate(Color king_color,Board* board) = 0;
    virtual bool is_stale_mate(Color king_color, Board* board) = 0;
    virtual bool would_move_cause_check(Move move, Board* board, Color king_color) = 0;
};