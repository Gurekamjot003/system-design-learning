#pragma once
#include"matching_strategy.hpp"

class ScoreBasedMatching: public MatchingStrategy{
    int score_tolerance;
    
public: 
    ScoreBasedMatching(int score_tolerance) : score_tolerance(score_tolerance) {}

    User* find_match(User* user, vector<User*>& queue) override {
        for (User* u : queue) {
            if (abs(user->get_score() - u->get_score()) <= score_tolerance) {
                return u;
            }
        }
        return nullptr;
    }

    void add_user_to_queue(User* user, vector<User*>& queue) override {
        queue.push_back(user);
        sort(queue.begin(), queue.end(), [](User* a, User* b) {
            return a->get_score() < b->get_score();
        });
    }

    void remove_user_from_queue(User* user, vector<User*>& queue) override {
        queue.erase(remove(queue.begin(), queue.end(), user), queue.end());
    }
};
