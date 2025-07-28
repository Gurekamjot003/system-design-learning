#pragma once
#include "symbol.hpp"

class Player{
    int id;
    static int next_id;
    string name;
    Symbol symbol;
    int score;
public:
    Player(string name, Symbol symbol): id(next_id++), name(name), symbol(symbol), score(0){}

    int get_id() const {
        return id;
    }
    string get_name() const {
        return name;
    }
    Symbol get_symbol() const {
        return symbol;
    }
    int get_score() const {
        return score;
    }
    void increment_score() {
        score++;
    }
    
};

int Player::next_id = 1;