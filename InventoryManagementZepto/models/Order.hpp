#pragma once
#include"User.hpp"
#include"DeliveryPartner.hpp"

class Order{
public:
    int order_id;
    static int next_id;
    User* user;
    vector<pair<Product*, int>> items;
    vector<DeliveryPartner*> delivery_partners;
    double total;

    Order(User* user):user(user), order_id(next_id++), total(0.0){}
};

int Order::next_id = 1;