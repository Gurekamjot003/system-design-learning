#ifndef MENUITEM_H
#define MENUITEM_H

#include<bits/stdc++.h>
using namespace std;

class MenuItem{
private:
    string code;
    string name;
    int price;

public:
    MenuItem(string code, string name, int price){
        this->code = code;
        this->name = name;
        this->price = price;
    }

    string get_code(){
        return code;
    }

    void set_code(string code){
        this->code = code;
    }

    string get_name(){
        return this->name;
    }
    
    void set_name(string name){
        this->name = name;
    }

    int get_price(){
        return this->price;
    }
    
    void set_price(int price){
        this->price = price;
    }


};

#endif