#pragma once
#include "colleague.hpp"

class User: public Colleague{
    string id;
    string name;
    int score;

public: 
    User(string id, string name, ChatMediator* mediator) : Colleague(mediator), id(id), name(name), score(1000) {}

    string get_id() const {
        return id;
    }

    string get_name() const {
        return name;
    }

    int get_score() const {
        return score;
    }

    void decrement_score(int points){
        score -= points;
    }

    void increment_score(int points){
        score += points;
    }

    string to_string(){
        return "User ID: " + id + ", Name: " + name + ", Score: " + std::to_string(score);
    }

    void receive_message(Message* message) override {
        cout << "User " << name << " received message: " << message->to_string() << endl;
    }

    void send_message(Message* message) override {
        if(mediator) mediator->send_message(*message);
    }
};