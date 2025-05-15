#include<bits/stdc++.h>
using namespace std;

class Car{
  public:
    virtual void start_engine() = 0;
    virtual void shift_gear(int gear) = 0;
    virtual void accelerate() = 0;
    virtual void brake() = 0;
    virtual void stop_engine() = 0;
    virtual ~Car(){}
};

class SportsCar: public Car{
  public:
    string brand;
    string model;
    bool is_engine_on;
    int current_speed;
    int current_gear;

    SportsCar(string b, string m){
        brand = b;
        model = m;
        is_engine_on = false;
        current_speed = 0;
        current_gear = 0;
    }

    void start_engine(){
        is_engine_on = true;
        cout<<brand<<" "<<model<<" : Engine starts with a roar!"<<endl;
    }
    
    void shift_gear(int gear){
        if(!is_engine_on){
            cout<<brand<<" "<<model<<" : Engine is off! Cannot shift gear."<<endl;
            return;
        }
        current_gear = gear;
        cout<<brand<<" "<<model<<" : Shifted to gear "<<current_gear<<endl;
    }
    
    void accelerate(){
        if(!is_engine_on){
            cout<<brand<<" "<<model<<" : Engine is off! Cannot accelerate."<<endl;
            return;
        }
        current_speed += 20;
        cout<<brand<<" "<<model<<" : Accelerating to "<<current_speed<<" km/h"<<endl;
    }
    
    void brake(){
        current_speed -= 20;
        current_speed = max(current_speed , 0);
        cout<<brand<<" "<<model<<" : Braking! Speed is now "<<current_speed<<" km/h"<<endl;
    }
    
    void stop_engine(){
        is_engine_on = false;
        current_gear = 0;
        current_speed = 0;
        cout<<brand<<" "<<model<<" : Engine turned off. "<<endl;
        
    }
};

int main(){
    Car* my_car = new SportsCar("Ford", "Mustang");
    my_car->start_engine();
    my_car->shift_gear(1);
    my_car->accelerate();
    my_car->shift_gear(2);
    my_car->accelerate();
    my_car->brake();
    my_car->stop_engine();
}