//Subtype overridden method return type should be either identical or narrower than the parent method's return type. 
// Also known as return type covariance.

#include<bits/stdc++.h>
using namespace std;

class Animal{

};

class Dog: public Animal{

};

class Parent{
public:
    virtual Animal* get_animal(){
        cout<<"Parent: Returning Animal instance"<<endl;
        return new Animal();
    }
};

class Child: public Parent{
public:
    Dog* get_animal(){
        cout<<"Child: Returning Dog instance"<<endl;
        return new Dog();
    }
};

class Client{
private:
    Parent* p;

public:
    Client(Parent* p){
        this->p = p;
    }
    void take_animal(){
        p->get_animal();
    }
}; 

int main(){
    Parent* parent = new Parent();
    Child* child = new Child();

    Client* client = new Client(child);
    client->take_animal();
}