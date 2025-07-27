#pragma once
#include"SplitStrategy.hpp"

class PercentSplit: public SplitStrategy{
public:
    vector<Split> calculate_split(double total_amount, vector<string> user_ids, vector<double> values = {}) override{
        vector<Split> splits;
        for(int i = 0; i<user_ids.size(); i++){
            splits.push_back(Split(user_ids[i], values[i]*total_amount/100));
        }
        return splits;
    }
};