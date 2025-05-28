#include<bits/stdc++.h>
using namespace std;

class Burger{
public:
    virtual void prepare() = 0;
    virtual ~Burger() {}
};

class BasicBurger: public Burger{
public:
    void prepare() override {
        cout<<"Preparing basic burger"<<endl;
    }
};

class StandardBurger: public Burger{
public:
    void prepare() override {
        cout<<"Preparing standard burger"<<endl;
    }
};

class PremiumBurger: public Burger{
public:
    void prepare() override {
        cout<<"Preparing premium burger"<<endl;
    }
};

class BurgerFactory{
public:
    Burger* create_burger(string type){
        if(type == "basic"){
            return new BasicBurger();
        }
        else if(type == "Standard"){
            return new StandardBurger();
        }
        else if(type == "Premium"){
            return new PremiumBurger();
        }
        else {
            cout<<"Invalid burger type!"<<endl;
            return NULL;
        }
    }
};

int main(){
    BurgerFactory* my_factory = new BurgerFactory();
    Burger* my_burger = my_factory->create_burger("basic");
    my_burger->prepare();
}