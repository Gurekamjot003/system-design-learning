#pragma once
#include "../models/DarkStore.hpp"

class DarkStoreManager{
    vector<DarkStore*> dark_stores; 
    static DarkStoreManager* instance;

    DarkStoreManager(){}

public:
    static DarkStoreManager* get_instance(){
        if(!instance) instance = new DarkStoreManager();
        return instance;
    }

    void register_dark_store(DarkStore* dark_store){
        dark_stores.push_back(dark_store);
    }

    vector<DarkStore*> get_nearby_stores(double user_x, double user_y, double max_distance){
        vector<pair<double, DarkStore*>> distance_list;
        for(auto& store: dark_stores){
            int cur_distance = store->distance_to(user_x, user_y);
            if( cur_distance <= max_distance)
                distance_list.push_back({cur_distance, store});
        }
        sort(distance_list.begin(), distance_list.end());
        vector<DarkStore*> ans;
        for(auto& it: distance_list){
            ans.push_back(it.second);
        }
        return ans;
    }

    ~DarkStoreManager(){
        for(auto store: dark_stores) delete store;
    }
};

DarkStoreManager* DarkStoreManager::instance = NULL;