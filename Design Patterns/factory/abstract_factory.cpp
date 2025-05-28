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

class GarlicBread{
public:
    virtual void prepare() = 0;
};

class BasicGarlicBread: public GarlicBread{
public:
    void prepare() override{
        cout<<"Preparing Basic Garlic Bread"<<endl;
    }
};

class CheeseGarlicBread: public GarlicBread{
public:
    void prepare() override{
        cout<<"Preparing Cheese Garlic Bread"<<endl;
    }
};

class BasicWheatGarlicBread: public GarlicBread{
public:
    void prepare() override{
        cout<<"Preparing Basic Wheat Garlic Bread"<<endl;
    }
};

class CheeseWheatGarlicBread: public GarlicBread{
public:
    void prepare() override{
        cout<<"Preparing Cheese Wheat Garlic Bread"<<endl;
    }
};

class BurgerFactory{
public:
    virtual Burger* create_burger(string type) = 0;
    virtual GarlicBread* create_garlic_bread(string type) = 0;
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
    
    GarlicBread* create_garlic_bread(string type) override {
        if(type == "basic"){
            return new BasicGarlicBread();
        }
        else if(type == "cheese"){
            return new CheeseGarlicBread();
        }
        else{
            cout<<"Invalid garlic bread type"<<endl;
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

    GarlicBread* create_garlic_bread(string type) override {
        if(type == "basic"){
            return new BasicWheatGarlicBread();
        }
        else if(type == "cheese"){
            return new CheeseWheatGarlicBread();
        }
        else{
            cout<<"Invalid garlic bread type"<<endl;
            return NULL;
        }
    }
};

int main(){
    BurgerFactory* my_factory = new SinghBurger();
    Burger* my_burger = my_factory->create_burger("basic");
    GarlicBread* my_garlic_bread = my_factory->create_garlic_bread("cheese");
    my_burger->prepare();
    my_garlic_bread->prepare();
}