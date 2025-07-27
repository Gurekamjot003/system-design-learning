#pragma once
#include<bits/stdc++.h>
using namespace std;

class Observer{
public:
    virtual void update(string msg) = 0;
};