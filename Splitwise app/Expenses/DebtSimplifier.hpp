#pragma once
#include<bits/stdc++.h>
using namespace std;

class DebtSimplifier{
public:
    static map<string, map<string, double>> simplifiy_debt(map<string, map<string, double>> group_balances){
        map<string, double> balances_left;
        for(auto&[p1, balances]: group_balances){
            for(auto&[p2, balance]: balances){
                balances_left[p1] -= balance;
                balances_left[p2] += balance;
            }
        }
        vector<pair<double, string>> balances_left_array;
        for(auto& [name, balance]: balances_left){
            balances_left_array.push_back({balance, name});
        }
        sort(balances_left_array.begin(), balances_left_array.end());
        
        
        
        int left = 0, right= balances_left_array.size()-1;        
        group_balances.clear();
        while(left<right){
            double neg_val = balances_left_array[left].first,
                pos_val = balances_left_array[right].first;
            string p1 = balances_left_array[left].second, p2 = balances_left_array[right].second;
            if(abs(neg_val) < pos_val){
                group_balances[p1][p2] = neg_val;
                group_balances[p2][p1] = -neg_val;
                balances_left_array[right].first += neg_val;
                left++;
            }
            else if(abs(neg_val) > pos_val){
                group_balances[p1][p2] = -pos_val;
                group_balances[p2][p1] = pos_val;
                balances_left_array[left].first -= pos_val;
                right--;
            }
            else{
                group_balances[p1][p2] = -pos_val;
                group_balances[p2][p1] = pos_val;
                left++;
                right--;
            }
        }
        return group_balances;
    }  
};