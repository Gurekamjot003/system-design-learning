#pragma once
#include<bits/stdc++.h>
using namespace std;

class BoardEntity{
public:

    int start;
    int end;

    BoardEntity(int start = 0, int end = 0) : start(start), end(end) {}
    virtual void display() = 0;
    virtual string name() = 0;
};