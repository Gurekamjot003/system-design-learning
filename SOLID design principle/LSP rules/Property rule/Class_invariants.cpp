//Class invariants (rules) of a parent class should not be broken by child class object.
//Child class can only maintain or strengthen the invriant but never narrows it down.

#include<bits/stdc++.h>
using namespace std;

//Invariant: Balance cannot be -ve
class BankAccount{
protected:
    int balance;

public:
    BankAccount(double balance){
        if(balance<0) throw invalid_argument("Balance can't be negative");
        this->balance = balance;
    }
    virtual void withdraw(int amount){
        if(amount>balance) throw runtime_error("Insufficient funds");
        balance -= amount;
        cout<<"Amount withdrawn! Remaining balance is "<<balance<<endl;
    }
};

//Invariant broken: should not be allowed
class CheatAccount: public BankAccount{

public:
    CheatAccount(double balance): BankAccount(balance){};

    void withdraw(int amount) override{
        balance -= amount;
        cout<<"Amount withdrawn! Remaining balance is "<<balance<<endl;
    }
};

int main(){
    BankAccount* account = new CheatAccount(100);
    account->withdraw(110);
}