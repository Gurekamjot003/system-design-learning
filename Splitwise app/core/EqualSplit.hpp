#pragma once
#include"SplitStrategy.hpp"

class EqualSplit: public SplitStrategy{
public:
    vector<Split> calculate_split(double total_amount, vector<string> user_ids, vector<double> values = {}) override{
        vector<Split> splits;
        double value = total_amount/(int)user_ids.size();
        for(int i = 0; i<user_ids.size(); i++){
            splits.push_back(Split(user_ids[i], value));
        }
        return splits;
    }
};