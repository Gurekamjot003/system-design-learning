#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include<bits/stdc++.h>
#include "../models/Order.h"
#include "../models/Cart.h"
#include "../models/Restaurant.h"
using namespace std;

class OrderFactory{
public:
    virtual Order* create_order(User* user, Cart* cart, Restaurant* restaurant, vector<MenuItem> menu_items, PaymentStrategy* payment_strategy, double total_cost, string order_type) = 0;

    virtual ~OrderFactory(){}
}; 

#endif