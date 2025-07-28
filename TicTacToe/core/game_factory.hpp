#pragma once
#include "gametype.hpp"
#include "game.hpp"

class GameFactory {
public: 
    static Game* create_game(GameType type, int board_size, Symbol empty_symbol) {
        switch(type) {
            case GameType::STANDARD:
                return new Game(board_size, empty_symbol, new StandardRules());
            default:
                throw invalid_argument("Unsupported game type");
        }
    }
};