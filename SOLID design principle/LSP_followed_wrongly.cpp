//Liskov's substituion principle
// child class should always extend parent class

#include<bits/stdc++.h>
using namespace std;

class Account{
    public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

class SavingAccount:public Account{
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

class CurrentAccount: public Account{
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

class FixedTermAccount: public Account{
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
    vector<Account*> accounts;

    public:
    BankClient(vector<Account*> accounts){
        this->accounts = accounts;
    }

    void process_transactions(){
        for(auto& account: accounts){
            account->deposit(1000);
            //THIS VIOLATES THE OCP
            if(typeid(*account) == typeid(FixedTermAccount)){
                cout<<"Skipping withdrawal for Fixed Term Account."<<endl;
            }
            else{
                try{
                    account->withdraw(500);
                }
                catch(const logic_error& e){
                    cout<<"Exception: "<<e.what()<<endl;
                }
            }
        }
    }
};

int main(){
    vector<Account*> accounts;
    accounts.push_back(new SavingAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FixedTermAccount());

    BankClient* client = new BankClient(accounts);
    client->process_transactions();
}