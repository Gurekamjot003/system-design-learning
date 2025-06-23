#pragma once
#include<bits/stdc++.h>
using namespace std;

class Product{
private:
    int sku;
    string name;
    double price;

public:
    Product(int sku, string name, double price): sku(sku), name(name), price(price){}

    int get_sku(){
        return sku;
    }

    string get_name(){
        return name;
    }
    
    double get_price(){
        return price;
    }
};