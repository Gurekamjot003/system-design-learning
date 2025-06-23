#pragma once
#include "../managers/InventoryManager.hpp"

class ReplenishStrategy{
public:
    virtual void replenish(InventoryManager* manager, map<int, int>& items_to_replenish) = 0;
};