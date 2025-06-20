#include<bits/stdc++.h>
using namespace std;

class IEngine{
public:
    virtual void start() = 0;
    virtual ~IEngine(){}
};

class PetrolEngine: public IEngine{
public:
    void start() override{
        cout<<"Petrol engine starting with ignition!"<<endl;
    }
};

class DieselEngine: public IEngine{
public:
    void start() override{
        cout<<"Diesel engine roaring to life!"<<endl;
    }
};

class ElectricEngine: public IEngine{
public:
    void start() override{
        cout<<"Electric engine powering up silently!"<<endl;
    }
};

class Car{
protected:
    IEngine* engine;

public:
    Car(IEngine* engine){
        this->engine = engine;
    }

    virtual void drive() = 0;

    virtual ~Car(){
        delete engine;
    }
};

class Sedan: public Car{
public:
    Sedan(IEngine* engine):Car(engine){}
    void drive() override{
        engine->start();
        cout<<"Driving a Sedan on highway"<<endl;
    }
};

class SUV: public Car{
public:
    SUV(IEngine* engine):Car(engine){}
    void drive() override{
        engine->start();
        cout<<"Driving a SUV off-road"<<endl;
    }
};

int main(){
    IEngine * petrol_engine = new PetrolEngine();
    IEngine * diesel_engine = new DieselEngine();
    IEngine * electric_engine = new ElectricEngine();


    Car* my_sedan = new Sedan(petrol_engine);
    Car* my_SUV= new SUV(diesel_engine);
    Car* my_eSUV= new SUV(electric_engine);

    my_sedan->drive();
    my_SUV->drive();
    my_eSUV->drive();

    delete my_sedan;
    delete my_SUV;
    delete my_eSUV;
}