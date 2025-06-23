#pragma once
#include "ReplenishStrategy.hpp"

class WeeklyReplenishStrategy: public ReplenishStrategy{
public:
    WeeklyReplenishStrategy(){}
    void replenish(InventoryManager* manager, map<int, int>& items_to_replenish) override{
        cout<<"[WeeklyReplenish] Weekly replenishment triggered for inventory."<<endl;
    }
};