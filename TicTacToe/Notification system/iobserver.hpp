#pragma once
#include<bits/stdc++.h>
using namespace std;

class IObserver{
public:
    virtual void update(string msg) = 0;
};