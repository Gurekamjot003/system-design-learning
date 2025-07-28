#pragma once
#include "board_setup_strategy.hpp"

#define vpii vector<pair<int, int>>

class customCountSetup : public BoardSetupStrategy {
    int num_snakes;
    int num_ladders;
    bool random_positions;
    vpii snakes;
    vpii ladders;
public:
    customCountSetup(int num_snakes, int num_ladders, bool random_positions = true)
        : num_snakes(num_snakes), num_ladders(num_ladders), random_positions(random_positions) {}

    void add_snake(int start, int end) {
        if (start <= end) {
            throw invalid_argument("Snake start must be greater than end");
        }
        snakes.push_back({start, end});
    }

    void add_ladder(int start, int end) {
        if (start >= end) {
            throw invalid_argument("Ladder start must be less than end");
        }
        ladders.push_back({start, end});
    }

    void setup(Board* board) override {
        if (random_positions) {
            srand(time(0)); 
            for (int i = 0; i < num_snakes; ++i) {
                int start = rand() % board->get_size() + 1;
                int end = start - (rand() % (board->get_size() / 10) + 1);
                while (!board->can_add_entity(start) or end<1 or end > board->get_size()) {
                    start = rand() % board->get_size() + 1;
                    end = start - (rand() % (board->get_size() / 10) + 1);
                }
                board->add_entity(new Snake(start, end));
            }
            for (int i = 0; i < num_ladders; ++i) {
                int start = rand() % board->get_size() + 1;
                int end = start + (rand() % (board->get_size() / 10) + 1);
                while (!board->can_add_entity(start) or end<1 or end > board->get_size()) {
                    start = rand() % board->get_size() + 1;
                    end = start + (rand() % (board->get_size() / 10) + 1);
                }
                board->add_entity(new Ladder(start, end));
            }
        }
        else{
            for (const auto& snake : snakes) {
                board->add_entity(new Snake(snake.first, snake.second));
            }
            for (const auto& ladder : ladders) {
                board->add_entity(new Ladder(ladder.first, ladder.second));
            }
        }
    }
};