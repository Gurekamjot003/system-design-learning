#ifndef USER_H
#define USER_H

#include<bits/stdc++.h>
#include "Cart.h"
using namespace std;

class User{
private:
    int user_id;
    string name;
    string address;
    Cart* cart;

public:
    User(int user_id, string name, string address){
        this->user_id = user_id;
        this->name = name;
        this->address = address;
        cart = new Cart();
    }

    ~User(){
        delete cart;
    }

    string get_name(){
        return name;
    }

    void set_name(string name){
        this->name = name;
    }

    string get_address(){
        return address;
    }

    void set_address(string address){
        this->address = address;
    }

    Cart* get_cart(){
        return cart;
    }

};

#endif