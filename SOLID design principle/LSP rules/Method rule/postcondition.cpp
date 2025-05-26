// A post condition must be satisfied after a method is executed
// subclasses can strengthen the postcondition but cannot weaken it.

#include<bits/stdc++.h>
using namespace std;

class Car{
protected:
    int speed;

public: 
    Car(){
        speed = 0;
    }

    void accelerate(){
        cout<<"Accelerating"<<endl;
        speed += 20;
    }

    // post condition: Speed must reduce
    virtual void brake(){
        cout<<"Braking"<<endl;
        speed -= 20;
    }
};

class HybridCar: public Car{
private:
    int charge;

public:
    HybridCar() : Car(){
        charge = 0;
    }

    // post condition: speed must reduce
    // post condition: chage must increase
    void brake(){
        cout<<"Braking"<<endl;
        speed -= 20;
        charge += 10;
    }
};

int main(){
    Car* car = new HybridCar();
    car->brake();
}