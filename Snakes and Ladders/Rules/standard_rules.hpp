#pragma once
#include "irules.hpp"

class StandardRules : public IRules {
public:
    bool is_valid_move(int cur_pos, int dice_value, int board_size) override {
        return (cur_pos + dice_value <= board_size);
    }

    int calculate_new_position(int cur_pos, int dice_value, Board* board) override {
        int new_position = cur_pos + dice_value;
        BoardEntity* entity = board->get_entity_at(new_position);

        if (entity) {

            return entity->end; // Move to the end of the snake or ladder
        }
        return new_position; // No entity, just move forward
    }

    bool check_winner(int position, int board_size) override {
        return position == board_size; // Winner if reached the last square
    }
};