//Liskov's substituion principle
// child class should always extend parent class

#include<bits/stdc++.h>
using namespace std;

class DepositOnlyAccount{
    public:
    virtual void deposit(double amount) = 0;
};

class WithdrawableAccount: public DepositOnlyAccount{
    public:
    virtual void withdraw(double amount) = 0;
};

class SavingAccount:public WithdrawableAccount{
    private:
    double balance;

    public:
    SavingAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited: "<<amount<<" in Savings Account. New Balance: "<<balance<<endl;
    }
    
    void withdraw(double amount){
        if(balance>=amount){
            balance -= amount;
            cout<<"Withdrawn: "<<amount<<" from Savings Account. New Balance: "<<balance<<endl;
        }
        else {
            cout<<"Insufficient funds in Savings Account!"<<endl;
        }
    }
};

class CurrentAccount: public WithdrawableAccount{
    private:
    double balance;

    public:
    CurrentAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited: "<<amount<<" in Current Account. New Balance: "<<balance<<endl;
    }
    
    void withdraw(double amount){
        if(balance>=amount){
            balance -= amount;
            cout<<"Withdrawn: "<<amount<<" from Current Account. New Balance: "<<balance<<endl;
        }
        else {
            cout<<"Insufficient funds in Current Account!"<<endl;
        }
    }
};

class FixedTermAccount: public DepositOnlyAccount{
    private:
    double balance;

    public:
    FixedTermAccount(){
        balance = 0;
    }

    void deposit(double amount){
        balance += amount;
        cout<<"Deposited: "<<amount<<" in Fixed Term Account. New Balance: "<<balance<<endl;
    }
    
    void withdraw(double amount){
        throw logic_error("Withdrawal not allowed in Fixed Term Account!");
    }
};

class BankClient{
    private:
    vector<WithdrawableAccount*> withdrawable_accounts;
    vector<DepositOnlyAccount*> deposit_only_accounts;

    public:
    BankClient(vector<WithdrawableAccount*> withdrawable_accounts, vector<DepositOnlyAccount*> deposit_only_accounts){
        this->withdrawable_accounts = withdrawable_accounts;
        this->deposit_only_accounts = deposit_only_accounts;
    }

    void process_transactions(){
        for(auto& account: withdrawable_accounts){
            account->deposit(1000);
            account->withdraw(500);
        }
        for(auto& account: deposit_only_accounts){
            account->deposit(1000);
        }
    }
};

int main(){
    vector<WithdrawableAccount*> withdrawable_accounts;
    withdrawable_accounts.push_back(new SavingAccount());
    withdrawable_accounts.push_back(new CurrentAccount());

    vector<DepositOnlyAccount*> deposit_only_accounts;
    deposit_only_accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(withdrawable_accounts, deposit_only_accounts);
    client->process_transactions();
}