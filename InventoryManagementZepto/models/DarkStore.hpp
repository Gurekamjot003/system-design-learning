#pragma once
#include "../strategies/ThresholdReaplenishStrategy.hpp"
#include "../strategies/WeeklyReplenishStrategy.hpp"

class DarkStore{
    string name;
    double x, y;
    InventoryManager* inventory_manager;
    ReplenishStrategy* replenish_strategy;
public:
    DarkStore(string name, double x, double y, ReplenishStrategy* replenish_strategy): name(name), x(x), y(y), replenish_strategy(replenish_strategy){
        inventory_manager = new InventoryManager(new DbInventoryStore());
    }

    ~DarkStore(){
        delete inventory_manager;
        delete replenish_strategy;
    }

    vector<Product*> get_all_products(){
        return inventory_manager->get_available_products();
    }

    double distance_to(double user_x, double user_y){
        return sqrt((x-user_x)*(x-user_x) + (y-user_y)*(y-user_y));
    }

    void run_replenish(map<int, int>& items_to_replenish){
        replenish_strategy->replenish(inventory_manager, items_to_replenish);
    }

    void remove_stock(int sku, int quantity){
        inventory_manager->remove_stock(sku, quantity);
    }

    int check_stock(int sku){
        return inventory_manager->check_stock(sku);
    }

    void add_stock(int sku, int quantity){
        inventory_manager->add_stock(sku, quantity);
    }

    void set_replenish_strategy(ReplenishStrategy* strategy){
        this->replenish_strategy = strategy;
    }

    string get_name(){
        return this->name;
    }

    pair<double, double> get_coordinate(){
        return {x, y};
    }

    InventoryManager* get_inventory_manager(){
        return inventory_manager;
    }
};