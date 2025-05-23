// Subtype method arguments can be identical or wider than the supertype
// automatic in cpp
#include<bits/stdc++.h>
using namespace std;

class Parent{
public:
    virtual void print(string msg){
        cout<<"Parent: "<<msg<<endl;
    }
};

class Child: public Parent{
public:
    void print(string msg) override{       // void print(int msg) will be wrong
        cout<<"Child: "<<msg<<endl;
    }
};

class Client{
private:
    Parent* p;

public:
    Client(Parent* p){
        this->p = p;
    }

    void print_msg(){
        p->print("Hello");
    }
};

int main(){
    Parent* parent = new Parent();
    Parent* child = new Child();

    Client* client = new Client(child);

    client->print_msg();
}