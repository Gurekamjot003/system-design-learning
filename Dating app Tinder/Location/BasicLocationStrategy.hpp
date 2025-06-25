#pragma once
#include"LocationStrategy.hpp"

class BasicLocationStrategy: public LocationStrategy{
public:
    vector<User*> find_nearby_users(Location* location, double max_distance, vector<User*> all_users, User* user){
        all_users.erase(find(all_users.begin(), all_users.end(), user));
        vector<User*> ans;
        for(auto& other_user: all_users){
            if(user->has_interacted_with(other_user->get_user_id())) continue;
            if(location->distance_in_km(other_user->get_location()) <= max_distance)
                ans.push_back(other_user);
        }
        return ans;
    }   
};