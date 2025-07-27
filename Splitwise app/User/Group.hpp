#pragma once
#include"../Expenses/Expense.hpp"
#include"../Expenses/DebtSimplifier.hpp"
#include"../core/SplitFactory.hpp"
#include"User.hpp"

class Group{

    User* get_user_by_id(string user_id){
        for(int i = 0; i<members.size(); i++){
            if(members[i]->user_id == user_id) return members[i];
        }
        return NULL;
    }
public:
    static int next_group_id;
    string group_id;
    string name;
    vector<User*> members;
    map<string, Expense*> group_expenses;
    map<string, map<string, double>> group_balances;

    Group(string name):name(name), group_id(to_string(next_group_id++)){}
    
    ~Group(){
        for(auto it: group_expenses) delete it.second;
    }

    void add_member(User* user){
        members.push_back(user);
        group_balances[user->user_id] = map<string, double>();
        cout<<user->name <<" added to group "<<name<<endl;
    }

    void simplify_group_debts(){
        map<string, map<string, double>> simplified_group_balances = DebtSimplifier::simplifiy_debt(group_balances);
        group_balances = simplified_group_balances;

        cout<<"\nDebts have been simplified for group: "<<name<<endl;
    }

    bool can_user_leave_group(string user_id){
        if(!is_member(user_id)) throw runtime_error("User is not a part of the group");

        simplify_group_debts();
        auto& user_balance_sheet = group_balances[user_id];
        for(auto& balance: user_balance_sheet){
            if(abs(balance.second) > 0.01) return false;
        }
        return true;
    }

    bool remove_member(string user_id){
        if(!can_user_leave_group(user_id)){
            cout<<"\nUser not allowed to leave the group before clearing outstanding balances"<<endl;
            return false;
        }
        for(int i = 0; i<members.size(); i++){
            auto user = members[i];
            if(user->user_id == user_id){
                members.erase(members.begin() + i);
                break;
            }
        }
        
        group_balances.erase(user_id);

        for(auto& it: group_balances){
            it.second.erase(user_id);
        }

        return true;
    }

    void notify_members(string msg){
        for(auto& observer: members) observer->update(msg);
    }

    bool is_member(string user_id){
        return group_balances.find(user_id) != group_balances.end();
    }

    void update_group_balance(string from_user_id, string to_user_id, double amount){
        group_balances[from_user_id][to_user_id] += amount;
        group_balances[to_user_id][from_user_id] -= amount;

        if(abs(group_balances[from_user_id][to_user_id]) < 0.01) group_balances[from_user_id].erase(to_user_id);
        if(abs(group_balances[to_user_id][from_user_id]) < 0.01) group_balances[to_user_id].erase(from_user_id);
    }

    map<string, double> get_user_group_balances(string user_id){
        if(!is_member(user_id)) throw runtime_error("User is not a part of the group");
        return group_balances[user_id];
    }
    
    bool add_expense(string description, double amount, string paid_by_user_id, vector<string>& involved_users, SplitType type, vector<double> split_values = {}){
        if(!is_member(paid_by_user_id)) throw runtime_error("User is not a part of the group");
        
        vector<Split> splits = SplitFactory::get_split_strategy(type)->calculate_split(amount, involved_users, split_values);
        
        Expense* expense = new Expense(description, amount, paid_by_user_id, splits, group_id);
        group_expenses[expense->id] = expense;
        
        for(auto& split: splits){
            if(split.user_id == paid_by_user_id) continue;
            update_group_balance(paid_by_user_id, split.user_id, split.amount);
        }
        
        cout<<"\n\nSending notification"<<endl;
        string paid_by_name = get_user_by_id(paid_by_user_id)->name;
        notify_members("New Expense added: " + description + " (Rs " + to_string(amount) + ")");
        
        cout<<"\n\nExpense message"<<endl;
        cout<<"Expense added to "<<name<<": "<<description<<" (Rs "<<amount<<") Paid by "<<paid_by_name<<" and involved people are: "<<endl;
        if(!split_values.empty()){
            for(int i = 0; i<split_values.size(); i++){
                cout<<get_user_by_id(involved_users[i])->name<<": "<<split_values[i]<<endl;
            }
        }
        else{
            for(auto& user_id: involved_users){
                cout<<get_user_by_id(user_id)->name<<endl;
            }
            cout<<"Will be paid equally"<<endl;
        }
        return true;
    }
    
    bool settle_payment(string from_user_id, string to_user_id, double amount){
        if(!is_member(from_user_id) or !is_member(to_user_id)){
            cout<<"User is not a part of this group"<<endl;
            return false;
        }

        update_group_balance(from_user_id, to_user_id, amount);

        notify_members("Settlement: " + get_user_by_id(from_user_id)->name + " paid " +  get_user_by_id(to_user_id)->name + " Rs " + to_string(amount));   

        cout<<"Settlement in "<< name << ": "<<get_user_by_id(from_user_id)->name<<" settled Rs "<<amount<<" with "<<get_user_by_id(to_user_id)->name<<endl;

        return true;
    }

    void show_group_balances(){
        cout<<"\nGroup Balances for "<<name<<endl;
        for(auto& [member_id, member_balances]: group_balances){
            string member_name = get_user_by_id(member_id)->name;

            cout<<member_name<<"'s balances in group: "<<endl;
            if(member_balances.empty()){
                cout<<"No outstanding balances"<<endl;
            }
            else{
                for(auto& [other_user_id, balance]: member_balances){
                    string other_name = get_user_by_id(other_user_id)->name;

                    if(balance>0){
                        cout<<"\t"<<other_name<<" owes: Rs "<<fixed<<setprecision(2)<<balance<<endl;
                    }
                    else{
                        cout<<"\tOwes "<<other_name<<": Rs "<<fixed<<setprecision(2)<<balance<<endl;
                    }
                }
            }
        }
    }
};

int Group::next_group_id = 0;