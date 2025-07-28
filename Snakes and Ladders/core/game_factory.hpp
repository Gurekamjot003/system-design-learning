#pragma once
#include "game.hpp"
#include "../Board setup/standard_board_setup.hpp"
#include "../Board setup/random_board_strategy.hpp"
#include "../Board setup/custom_count_setup.hpp"

class GameFactory {
public:
    static Game* create_standard_game() {
        Board* board = new Board(10); // 10x10 board
        Dice* dice = new Dice();
        IRules* rules = new StandardRules();
        Game* game = new Game(board, dice, rules);
        
        // Setup the board with standard entities
        StandardBoardSetup setup;
        setup.setup(board);
        
        return game;
    }

    static Game* create_random_game(int board_size, Difficulty difficulty) {
        Board* board = new Board(board_size);
        Dice* dice = new Dice();
        IRules* rules = new StandardRules();
        Game* game = new Game(board, dice, rules);
        
        // Setup the board with random entities based on difficulty
        RandomBoardStrategy setup(difficulty);
        setup.setup(board);
        
        return game;
    }

    static Game* create_custom_game(int board_size, int num_snakes, int num_ladders, bool random_positions = true) {
        Board* board = new Board(board_size);
        Dice* dice = new Dice();
        IRules* rules = new StandardRules();
        Game* game = new Game(board, dice, rules);
        
        // Setup the board with custom entities
        customCountSetup setup(num_snakes, num_ladders, random_positions);
        setup.setup(board);
        
        return game;
    }
};