#pragma once
#include<bits/stdc++.h>
using namespace std;

class Interest{
public:
    string name;
    string category;

    Interest(string name, string category) : name(name), category(category){}

    string get_interest(){
        return name + " - " + category;
    }

    string get_name(){
        return name;
    }
};