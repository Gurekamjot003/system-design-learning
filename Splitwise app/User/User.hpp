#pragma once 
#include"Observer.hpp"

class User:public Observer{
public:
    static int next_user_id;
    string user_id;
    string name;
    string email;
    map<string, double> balances;

    User(string name, string email):name(name), email(email), user_id(to_string(next_user_id++)){}

    void update(string msg) override{
        cout<<"[Notification to "<<name<<"]: "<<msg<<endl;
    }

    void update_balances(string other_user_id, double amount){
        balances[other_user_id] += amount;
        if(balances[other_user_id] == 0) balances.erase(other_user_id);

    }

    double get_total_owed(){
        double total = 0;
        for(auto& balance: balances){
            if(balance.second<0)
            total += abs(balance.second);
        }
        return total;
    }

    double get_total_owing(){
        double total = 0;
        for(auto& balance: balances){
            if(balance.second>0) total+= balance.second;
        }
        return total;
    }
};

int User::next_user_id = 0;