#pragma once
#include "ReplenishStrategy.hpp"

class ThresholdReplenishStrategy: public ReplenishStrategy{
    int threshold;

public:
    ThresholdReplenishStrategy(int threshold) : threshold(threshold){}

    void replenish(InventoryManager* manager, map<int, int>& items_to_replenish) override{
        cout<<"[ThresholdReplenish] Checking threshold..."<<endl;
        for(auto& it: items_to_replenish){
            int sku = it.first, quantity = it.second;
            int cur_quantity = manager->check_stock(sku);
            if(cur_quantity<threshold){
                manager->add_stock(sku, quantity);
                cout<<" -> SKU "<<sku<<" was "<<cur_quantity<<", replenished by "<<quantity<<endl;       
            }
        }
    }  
};