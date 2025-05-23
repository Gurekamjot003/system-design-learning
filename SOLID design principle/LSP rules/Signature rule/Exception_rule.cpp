// A subclass should throw fewer or narrower exceptions (but not additional or broader exceptions) than the parent.
// *cpp does not enforce this*

#include<bits/stdc++.h>
using namespace std;

class Parent{
public:
    virtual void get_value() noexcept(false){
        throw logic_error("Parent error");
    }
};

class Child: public Parent{
public:
    void get_value() noexcept(false) override{
        throw out_of_range("Child error");
    }
};

class Client{
private:
    Parent* p;

public:
    Client(Parent* p){
        this->p = p;
    }
    void take_value(){
        try{
            p->get_value();
        }
        catch(const logic_error& e){
            cout<<"logic error exception occured: "<<e.what()<<endl;
        }
    }
};

int main(){
    Parent* parent = new Parent();
    Child* child = new Child();

    Client* client = new Client(child);

    client->take_value();
}