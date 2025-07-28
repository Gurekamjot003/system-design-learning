#pragma once
#include "board_entity.hpp"

class Ladder:public BoardEntity{
public:
    Ladder(int start, int end) : BoardEntity(start, end) {
        if (start >= end) {
            throw invalid_argument("Ladder start must be less than end");
        }
    }

    void display() override {
        cout << "Ladder from " << start << " to " << end << endl;
    }
    string name() override {
        return "Ladder";
    }
};