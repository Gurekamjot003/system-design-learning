#pragma once
#include <bits/stdc++.h>
using namespace std;

class IObserver{
public:
    virtual void update(string& message) = 0;
};