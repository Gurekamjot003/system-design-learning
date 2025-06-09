#ifndef ORDER_H
#define ORDER_H

#include<bits/stdc++.h>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../Strategies/PaymentStrategy.h"
#include "../Utils/TimeUtils.h"
using namespace std;

class Order{
protected:
    static int next_order_id;
    int order_id;
    User* user;
    Restaurant* restaurant;
    vector<MenuItem> items;
    PaymentStrategy* payment_strategy;
    double total;
    string scheduled;  
    
public:
    Order(){
        user = NULL;
        restaurant = NULL;
        payment_strategy = NULL;
        total = 0;
        scheduled = "";
        order_id = ++next_order_id;
    }

    ~Order(){
        delete payment_strategy;
    }

    bool process_payment(){
        if(payment_strategy){
            payment_strategy->pay(total);
            return true;
        }
        else{
            cout<<"Please select a payment mode first."<<endl;
            return false;
        }
    }

    virtual string get_type() = 0;

    int get_order_id(){
        return order_id;
    }

    void set_user(User* user){
        this->user = user;
    }

    User* get_user(){
        return user;
    }

    void set_restaurant(Restaurant* r){
        this->restaurant = r;
    }

    Restaurant* get_restaurant(){
        return restaurant;
    }

    void set_items(vector<MenuItem> items){
        this->items = items;
        total = 0;
        for(auto& item: items){
            total += item.get_price();
        }
    }

    vector<MenuItem> get_items(){
        return items;
    }

    void set_payment_strategy(PaymentStrategy* p){
        this->payment_strategy = p;
    }

    void set_scheduled(string s){
        scheduled = s;
    }

    string get_schedule(){
        return scheduled;
    }

    double get_total(){
        return total;
    }

    void set_total(int total){
        this->total = total;
    }
};

int Order::next_order_id = 0;

#endif