#pragma once
#include "Cart.hpp"

class User{
public:
    string name;
    double x, y;
    Cart* cart;

    User(string name, double x, double y): name(name), x(x), y(y), cart(new Cart()){}

    ~User(){
        delete cart;
    }

    Cart* get_cart(){
        return cart;
    }
};