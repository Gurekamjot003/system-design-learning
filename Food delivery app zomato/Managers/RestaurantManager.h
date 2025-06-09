#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include<bits/stdc++.h>
#include "../models/Restaurant.h"
using namespace std;

class RestaurantManager{
private:   
    vector<Restaurant*> restaurants;
    static RestaurantManager* instance;

    RestaurantManager(){

    }

public:
    static RestaurantManager* get_instance(){
        if(!instance){
            instance = new RestaurantManager();
        }
        return instance;
    }

    void add_restaurant(Restaurant* rs){
        restaurants.push_back(rs);
    }
    
    vector<Restaurant*> search_by_location(string loc){
        vector<Restaurant*> ans;
        for(int i = 0; i<loc.size(); i++){
            loc[i] = tolower(loc[i]);
        }
        // transform(loc.begin(), loc.end(), loc.begin(), ::tolower);

        for(auto& r: restaurants){
            string rl = r->get_location();
            transform(rl.begin(), rl.end(), rl.begin(), ::tolower);
            if(rl == loc) ans.push_back(r);
        }
        return ans;
    }

};

RestaurantManager* RestaurantManager::instance = NULL;

#endif