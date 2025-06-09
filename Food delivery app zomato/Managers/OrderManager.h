#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include<bits/stdc++.h>
#include "../models/Order.h"
using namespace std;

class OrderManager{
private:
    vector<Order*> orders;
    static OrderManager* instance;

    OrderManager(){

    }

public:
    static OrderManager* get_instance(){
        if(!instance){
            instance = new OrderManager();
        }
        return instance;
    }

    void add_order(Order* order){
        orders.push_back(order);
    }

    void list_orders(){
        cout<<"\nAll Orderes:"<<endl;
        for(auto& order: orders){
            cout<<order->get_type()<<" order for "<<order->get_user()->get_name()<<" | Total: Rs. "<<order->get_total()<<" | At: "<<order->get_schedule()<<endl;
        }
    }
};

OrderManager* OrderManager::instance = NULL;

#endif