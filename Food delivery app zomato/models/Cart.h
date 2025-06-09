#ifndef CART_H
#define CART_H

#include<bits/stdc++.h>
#include "Restaurant.h"
using namespace std;

class Cart{
private:
    Restaurant* restaurant;
    vector<MenuItem> items;

public: 
    Cart(){
        restaurant = NULL;
    }

    void add_item(MenuItem item){
        if(!restaurant){
            cerr<<"Cart: set a restaurant before adding items."<<endl;
            return;
        }
        items.push_back(item);
    }

    double get_total_cost(){
        double sum = 0;
        for(auto& item: items){
            sum += item.get_price();
        }
        return sum;
    }

    bool is_emtpy(){
        return (!restaurant or items.empty());
    }

    void clear(){
        items.clear();
        restaurant = NULL;
    }

    void set_restaurant(Restaurant* r){
        this->restaurant = r;
    }

    Restaurant* get_restaurant(){
        return restaurant;
    }

    vector<MenuItem> get_items(){
        return items;
    }
};

#endif