#pragma once
#include "../core/board.hpp"

class IRules{
public:
    virtual bool is_valid_move(Board* board, int row, int col) = 0;
    virtual bool is_winner(Board* board, int row, int col) = 0;
    virtual bool is_draw(Board* board) = 0;
};
