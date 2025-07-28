#pragma once
#include <bits/stdc++.h>
using namespace std;

class Player{
private:
    int id;
    static int next_id;
    string name;
    int position;
    int score;

public: 
    Player(string name): id(next_id++), name(name), position(0), score(0){}

    int getId() const {
        return id;
    }
    string getName() const {
        return name;
    }
    int getPosition() const {
        return position;
    }
    void setPosition(int new_position) {
        position = new_position;
    }
    int getScore() const {
        return score;
    }
    void increment_score() {
        score++;
    }
    void display() const {
        cout << "Player ID: " << id << ", Name: " << name 
             << ", Position: " << position << ", Score: " << score << endl;
    }

};

int Player::next_id = 1; // Initialize static member variable