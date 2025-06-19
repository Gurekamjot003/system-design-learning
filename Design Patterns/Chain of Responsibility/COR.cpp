#include<bits/stdc++.h>
using namespace std;

class MoneyHandler{
protected:
    MoneyHandler* next_handler;

public:
    MoneyHandler(){
        next_handler = NULL;
    }

    void set_next_handler(MoneyHandler* next){
        this->next_handler = next;
    }

    virtual void dispense(int amount) = 0;
};

class ThousandHandler: public MoneyHandler{
private:
    int num_notes;

public:
    ThousandHandler(int num_notes){
        this->num_notes = num_notes;
    }

    void dispense(int amount) override{
        int notes_req = amount/1000;
        if(notes_req > num_notes){
            notes_req = num_notes;
            num_notes = 0;
        }
        else num_notes -= notes_req;

        if(notes_req>0)
            cout<<"Dispensing "<<notes_req<<" x 1000 rs notes."<<endl;
        
        int remaining_amount = amount - notes_req*1000;
        if(remaining_amount>0){
            if(next_handler)next_handler->dispense(remaining_amount);
            else{
                cout<<"Remaining amount of "<<remaining_amount<<" cannot be fulfilled(Insufficient fund in ATM)"<<endl;
            }
        }
    }
};

class FiveHundredHandler: public MoneyHandler{
private:
    int num_notes;

public:
    FiveHundredHandler(int num_notes){
        this->num_notes = num_notes;
    }

    void dispense(int amount) override{
        int notes_req = amount/500;
        if(notes_req > num_notes){
            notes_req = num_notes;
            num_notes = 0;
        }
        else num_notes -= notes_req;

        if(notes_req>0)
            cout<<"Dispensing "<<notes_req<<" x 500 rs notes."<<endl;
        
        int remaining_amount = amount - notes_req*500;
        if(remaining_amount>0){
            if(next_handler)next_handler->dispense(remaining_amount);
            else{
                cout<<"Remaining amount of "<<remaining_amount<<" cannot be fulfilled(Insufficient fund in ATM)"<<endl;
            }
        }
    }
};

class TwoHundredHandler: public MoneyHandler{
private:
    int num_notes;

public:
    TwoHundredHandler(int num_notes){
        this->num_notes = num_notes;
    }

    void dispense(int amount) override{
        int notes_req = amount/200;
        if(notes_req > num_notes){
            notes_req = num_notes;
            num_notes = 0;
        }
        else num_notes -= notes_req;

        if(notes_req>0)
            cout<<"Dispensing "<<notes_req<<" x 200 rs notes."<<endl;
        
        int remaining_amount = amount - notes_req*200;
        if(remaining_amount>0){
            if(next_handler)next_handler->dispense(remaining_amount);
            else{
                cout<<"Remaining amount of "<<remaining_amount<<" cannot be fulfilled(Insufficient fund in ATM)"<<endl;
            }
        }
    }
};

class HundredHandler: public MoneyHandler{
private:
    int num_notes;

public:
HundredHandler(int num_notes){
        this->num_notes = num_notes;
    }

    void dispense(int amount) override{
        int notes_req = amount/100;
        if(notes_req > num_notes){
            notes_req = num_notes;
            num_notes = 0;
        }
        else num_notes -= notes_req;

        if(notes_req>0)
            cout<<"Dispensing "<<notes_req<<" x 100 rs notes."<<endl;
        
        int remaining_amount = amount - notes_req*100;
        if(remaining_amount>0){
            if(next_handler)next_handler->dispense(remaining_amount);
            else{
                cout<<"Remaining amount of "<<remaining_amount<<" cannot be fulfilled(Insufficient fund in ATM)"<<endl;
            }
        }
    }
};

int main(){
    MoneyHandler* thousand = new ThousandHandler(3);
    MoneyHandler* five_hundred = new FiveHundredHandler(5);
    MoneyHandler* two_hundred = new TwoHundredHandler(10);
    MoneyHandler* one_hundred = new HundredHandler(20);

    thousand->set_next_handler(five_hundred);
    five_hundred->set_next_handler(two_hundred);
    two_hundred->set_next_handler(one_hundred);

    int amount_to_withdraw = 4000;

    cout<<"Dispensing amount: Rs. "<<amount_to_withdraw<<endl;
    thousand->dispense(amount_to_withdraw);
}