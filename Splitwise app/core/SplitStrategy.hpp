#pragma once
#include"Split.hpp"

class SplitStrategy{
public:
    virtual vector<Split> calculate_split(double total_amount, vector<string> user_ids, vector<double> values = {}) = 0;
};