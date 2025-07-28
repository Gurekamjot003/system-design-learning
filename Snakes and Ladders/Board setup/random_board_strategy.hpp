#pragma once
#include "board_setup_strategy.hpp"
#include "difficulty.hpp"

class RandomBoardStrategy : public BoardSetupStrategy {
    Difficulty difficulty;
public:
    RandomBoardStrategy(Difficulty diff) : difficulty(diff) {}

    void setup(Board* board) override{
        int num_entities = board->get_size() / 10; // Example: 10% of the board size
        double probability_of_snake;

        switch (difficulty) {
            case Difficulty::EASY:
                probability_of_snake = 0.2; // 20% chance of snake
                break;
            case Difficulty::MEDIUM:
                probability_of_snake = 0.5; // 50% chance of snake
                break;
            case Difficulty::HARD:
                probability_of_snake = 0.8; // 80% chance of snake
                break;
        }
        srand(time(0)); // Seed for random number generation
        for (int i = 0; i < num_entities; ++i) {
            double prob = static_cast<double>(rand()) / RAND_MAX;
            int start = 0;

            while(start < 1 || start > board->get_size() || !board->can_add_entity(start)) {
                start = rand() % board->get_size() + 1; // Random position on the board
            }
            int end = 0;
            if(prob < probability_of_snake){
                end = start - (rand() % (board->get_size() / 10) + 1); // Snake goes down
                while(board->can_add_entity(start) == false or end<1 or end > board->get_size()) 
                    end = start - (rand() % (board->get_size() / 10) + 1);
                board->add_entity(new Snake(start, end));
            }
            else {
                end = start + (rand() % (board->get_size() / 10) + 1); // Ladder goes up
                while(board->can_add_entity(start) == false or end<1 or end > board->get_size()) 
                    end = start + (rand() % (board->get_size() / 10) + 1);
                board->add_entity(new Ladder(start, end));
            }
        }
    }
};