#pragma once

#include<bits/stdc++.h>
using namespace std;

class Symbol{
    char mark;
public:
    Symbol(char mark): mark(mark){}

    char get_mark(){
        return mark;
    }
};