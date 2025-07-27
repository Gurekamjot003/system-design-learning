#pragma once
#include"User/Group.hpp"

class Splitwise{
    map<string, User*> users;
    map<string, Group*> groups;
    map<string, Expense*> expenses;
    static Splitwise* instance;

    Splitwise(){}

public:
    static Splitwise* get_instance(){
        if(instance == NULL) instance = new Splitwise();
        return instance;
    }

    User* create_user(string name, string email){
        User* user = new User(name, email);
        users[user->user_id] = user;
        cout<<"User create: "<<name<<" (ID: " <<user->user_id<<")"<<endl;
        return user;
    }

    User* get_user(string user_id){
        if(users.find(user_id) == users.end()) return NULL;
        return users[user_id];
    }

    Group* create_group(string name){
        Group* group = new Group(name);
        groups[group->group_id] = group;
        return group;
    }

    Group* get_group(string group_id){
        if(groups.find(group_id) == groups.end()) return NULL;
        return groups[group_id];
    }

    void add_user_to_group(string user_id, string group_id){
        auto user = get_user(user_id);
        auto group = get_group(group_id);
        if(user && group){
            group->add_member(user);
        }
    }
    
    bool remove_user_from_group(string user_id, string group_id){
        auto user = get_user(user_id);
        auto group = get_group(group_id);
        bool user_removed;
        if(user && group){
            if(group->is_member(user_id))
            user_removed = group->remove_member(user_id);
        }
        if(user_removed) cout<<user->name<<" Successfully left "<<group->name<<endl;
        return user_removed;
        
    }

    void add_expense_to_group(string group_id, string description, double amount, string paid_by_user_id, vector<string>& involved_users, SplitType split_type, vector<double> split_values = {}){

        Group* group = get_group(group_id);

        if(!group){
            cout<<"Group not found"<<endl;
            return;
        }
        group->add_expense(description, amount, paid_by_user_id, involved_users, split_type, split_values);
    }

    void settle_payment_in_group(string group_id, string from_user_id, string to_user_id, double amount){
        Group* group = get_group(group_id);
        if(!group){
            cout<<"Group not found"<<endl;
            return;
        }
        group->settle_payment(from_user_id, to_user_id, amount);
    }

    void settle_individual_payment(string from_user_id, string to_user_id, double amount){
        User* from_user = get_user(from_user_id);
        User* to_user = get_user(to_user_id);

        if(from_user && to_user){
            from_user->update_balances(to_user_id, amount);
            to_user->update_balances(from_user_id, -amount);
            cout<<from_user<<" settled Rs "<<amount<<" with "<<to_user->name<<endl;
        }
    }

    void add_individual_expense(string description, double amount, string paid_by_user_id, string to_user_id, SplitType split_type, vector<double> split_values = {}){
        SplitStrategy* strategy = SplitFactory::get_split_strategy(split_type);
        vector<Split> splits = strategy->calculate_split(amount, {paid_by_user_id, to_user_id}, split_values);

        Expense* expense = new Expense(description, amount, paid_by_user_id, splits);
        expenses[expense->id] = expense;

        User* paid_by_user = get_user(paid_by_user_id);
        User* to_user = get_user(to_user_id);

        paid_by_user->update_balances(to_user_id, amount);
        to_user->update_balances(paid_by_user_id, -amount);

        cout<<"Individual expense added "<<description<<" (Rs "<< amount<<") paid by "<<paid_by_user->name<<" for "<<to_user->name<<endl;
    }

    void show_user_balance(string user_id){
        User* user = get_user(user_id);

        if(!user) return;

        cout<<"\n\nShowing balance for "<<user->name<<endl;
        cout<<"Total owing "<<fixed<<setprecision(2)<<user->get_total_owing()<<endl;
        cout<<"Total owed "<<fixed<<setprecision(2)<<user->get_total_owed()<<endl;


        cout<<"Detailed balances:"<<endl;
        for(auto& [other_user_id, balance]: user->balances){
            User* other_user = get_user(other_user_id);
            if(other_user){
                if(balance>0) cout<<"\t"<<other_user->name<< " owes you Rs "<<balance<<endl;
                else cout<<"\tYou owe "<<other_user->name<< " Rs "<<abs(balance)<<endl;
            }
        }
    }

    void show_group_balances(string group_id){
        Group* group = get_group(group_id);
        if(!group){
            cout<<"Group not found"<<endl;
            return;
        }
        
        group->show_group_balances();
    }
    
    void simplify_debts(string group_id){
        Group* group = get_group(group_id);
        if(!group){
            cout<<"Group not found"<<endl;
            return;
        }

        group->simplify_group_debts();
    }


};

Splitwise* Splitwise::instance =  NULL;