#pragma once
#include "../Board/board.hpp"
#include "difficulty.hpp"

class Board;

class BoardSetupStrategy {
public:
    virtual void setup(Board* board) = 0;

    virtual ~BoardSetupStrategy() = default; // Virtual destructor for proper cleanup of derived classes
};

