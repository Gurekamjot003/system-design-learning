#pragma once
#include "board_setup_strategy.hpp"

class StandardBoardSetup : public BoardSetupStrategy {
public:
    void setup(Board* board) override {

        if(board->get_size() != 100) {
            throw invalid_argument("Standard setup requires a board size of 10x10 (100 squares)");
        }

        // Example setup: Adding a few snakes and ladders
        board->add_entity(new Snake(99, 54));
        board->add_entity(new Snake(95, 75));
        board->add_entity(new Snake(92, 88));
        board->add_entity(new Snake(89, 68));
        board->add_entity(new Snake(74, 53));
        board->add_entity(new Snake(64, 60));
        board->add_entity(new Snake(62, 19));
        board->add_entity(new Snake(49, 11));
        board->add_entity(new Snake(46, 25));
        board->add_entity(new Snake(16, 6));

        board->add_entity(new Ladder(2, 38));
        board->add_entity(new Ladder(7, 14));
        board->add_entity(new Ladder(8, 31));
        board->add_entity(new Ladder(15, 26));
        board->add_entity(new Ladder(21, 42));
        board->add_entity(new Ladder(28, 84));
        board->add_entity(new Ladder(36, 44));
        board->add_entity(new Ladder(51, 67));
        board->add_entity(new Ladder(71, 91));
        board->add_entity(new Ladder(78, 98));
        board->add_entity(new Ladder(87, 94));
    }

    ~StandardBoardSetup() override = default; // Ensure proper cleanup
};