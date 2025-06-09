#ifndef PICKUP_ORDER_H
#define PICKUP_ORDER_H

#include <bits/stdc++.h>
#include "Order.h"
using namespace std;

class PickupOrder: public Order{
private:
    string restaurant_address;

public:
    PickupOrder(){
        restaurant_address = "";
    }    

    string get_type() override{
        return "Pickup";
    }

    void set_restaurant_address(string address){
        this->restaurant_address = address;
    }

    string get_restaurant_address(){
        return restaurant_address;
    }


};

#endif