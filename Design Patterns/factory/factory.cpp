#include<bits/stdc++.h>
using namespace std;

class Burger{
public:
    virtual void prepare() = 0;
    virtual ~Burger() {}
};

class BasicBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing basic burger"<<endl;
    }
};

class StandardBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing standard burger"<<endl;
    }
};

class PremiumBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing premium burger"<<endl;
    }
};

class BasicWheatBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing basic wheat burger"<<endl;
    }
};

class StandardWheatBurger: public Burger{
public:
    void prepare() override {
        cout<<"Preparing standard wheat burger"<<endl;
    }
};

class PremiumWheatBurger: public Burger{
public:
    void prepare() override{
        cout<<"Preparing premium wheat burger"<<endl;
    }
};

class BurgerFactory{
public:
    virtual Burger* create_burger(string type) = 0;
};

class KingBurger: public BurgerFactory{
public:
    Burger* create_burger(string type) override {
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

class SinghBurger: public BurgerFactory{
public:
    Burger* create_burger(string type) override {
        if(type == "basic"){
            return new BasicWheatBurger();
        }
        else if(type == "Standard"){
            return new StandardWheatBurger();
        }
        else if(type == "Premium"){
            return new PremiumWheatBurger();
        }
        else {
            cout<<"Invalid burger type!"<<endl;
            return NULL;
        }
    }
};

int main(){
    BurgerFactory* my_factory = new SinghBurger();
    Burger* my_burger = my_factory->create_burger("basic");
    my_burger->prepare();
}