// subclass methods should not be allowed state changes which base class never allowed

#include<bits/stdc++.h>
using namespace std;

class BankAccount{
protected:
    int balance;

public:
    BankAccount(double balance){
        if(balance<0) throw invalid_argument("Balance can't be negative");
        this->balance = balance;
    }

    // history constraint: withdrawal should always be allowed
    virtual void withdraw(int amount){
        if(amount>balance) throw runtime_error("Insufficient funds");
        balance -= amount;
        cout<<"Amount withdrawn! Remaining balance is "<<balance<<endl;
    }
};

class FixedDepositAccout: public BankAccount{

public:
    FixedDepositAccout(double balance): BankAccount(balance){};

    //history constraint broken
    void withdraw(int amount) override{
        throw runtime_error("Withdraw not allowed in Fixed Deposit");
    }
};

int main(){
    BankAccount* account = new FixedDepositAccout(100);
    account->withdraw(50);
}