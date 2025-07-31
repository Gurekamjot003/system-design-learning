#pragma once
#include "match.hpp"

class MatchingStrategy{
    
public:
    virtual User* find_match(User* user, vector<User*>& queue) = 0;
    virtual void add_user_to_queue(User* user, vector<User*>& queue) = 0;
    virtual void remove_user_from_queue(User* user, vector<User*>& queue) = 0;
};
