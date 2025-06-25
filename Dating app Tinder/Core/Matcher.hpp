#pragma once
#include "../User/User.hpp"

class Matcher{
public:
    virtual double calculate_match_score(User* user1, User* user2) = 0;
};