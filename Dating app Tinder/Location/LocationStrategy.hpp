#pragma once
#include "../User/User.hpp"

class LocationStrategy{
public:
    virtual vector<User*> find_nearby_users(Location* location, double max_distance, vector<User*> all_users, User* user) = 0;
};
