#pragma once
#include"board_entity.hpp"

class Snake: public BoardEntity{
public:
    Snake(int start, int end) : BoardEntity(start, end) {
        if (start <= end) {
            throw invalid_argument("Snake start must be greater than end");
        }
    }

    void display() override {
        cout << "Snake from " << start << " to " << end << endl;
    }

    string name() override{
        return "Snake";
    }
};