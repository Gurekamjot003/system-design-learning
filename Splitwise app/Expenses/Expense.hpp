#pragma once
#include"../core/Split.hpp"
#include<bits/stdc++.h>
using namespace std;

class Expense{
public:
    static int next_expense_id;
    string id;
    double amount;
    string description;
    string paid_user_id;
    vector<Split> splits;
    string group_id;

    Expense(string description, double amount, string paid_by, vector<Split> splits, string group_id = ""):amount(amount), paid_user_id(paid_by), splits(splits), group_id(group_id), id(to_string(next_expense_id)), description(description){}

};

int Expense::next_expense_id = 0;