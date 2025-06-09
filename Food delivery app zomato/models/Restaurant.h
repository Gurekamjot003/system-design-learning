#ifndef RESTAURANT_H
#define RESTAURANT_H

#include<bits/stdc++.h>
#include"MenuItem.h"
using namespace std;

class Restaurant{
private:
    static int next_restaurant_id;
    int restaurant_id;
    string name;
    string location;
    vector<MenuItem> menu;

public:
    Restaurant(string name, string location){
        this->restaurant_id = ++next_restaurant_id;
        this->location = location;
        this->name = name;
    }

    ~Restaurant(){
        cout<<"Destroying Restaurant: "<<name<<", and clearing its menu."<<endl;
        menu.clear();
    }

    string get_name(){
        return this->name;
    }

    void set_name(string name){
        this->name = name;
    }

    string get_location(){
        return this->location;
    }

    void set_location(string location){
        this->location = location;
    }

    vector<MenuItem> get_menu(){
        return this->menu;
    }

    void add_menu_item(MenuItem item){
        menu.push_back(item);
    }
};

int Restaurant::next_restaurant_id = 0;

#endif