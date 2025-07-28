#pragma once
#include "../Board/board.hpp"

class IRules{
public:
    virtual bool is_valid_move(int cur_pos, int dice_value, int board_size) = 0;
    virtual int calculate_new_position(int cur_pos, int dice_value, Board* board) = 0;
    virtual bool check_winner(int position, int board_size) = 0;
};