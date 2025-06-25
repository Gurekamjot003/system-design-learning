#pragma once
#include "BasicLocationStrategy.hpp"

class LocationService{
    LocationStrategy* location_strategy;
    static LocationService* instance;
    LocationService(){
        location_strategy = new BasicLocationStrategy();
    }
public:

    static LocationService* get_instance(){
        if(!instance) instance = new LocationService();
        return instance;
    }

    void set_strategy(LocationStrategy* strategy){
        location_strategy = strategy;
    }

    vector<User*> find_nearby_users(Location* location, double max_distance, vector<User*> all_users, User* user){
        return location_strategy->find_nearby_users(location, max_distance, all_users, user);
    }

    ~LocationService(){
        delete location_strategy;
    }
};

LocationService* LocationService::instance = NULL;