#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include <bits/stdc++.h>
#include "Order.h"
using namespace std;

class DeliveryOrder: public Order{
private:
    string user_address;

public:
    DeliveryOrder(){
        user_address = "";
    }    

    string get_type() override{
        return "Delivery";
    }

    void set_user_address(string address){
        this->user_address = address;
    }

    string get_user_address(){
        return user_address;
    }


};

#endif