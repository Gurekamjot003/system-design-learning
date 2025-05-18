#include<bits/stdc++.h>
using namespace std;

class Manual_Car{
  private:
    string brand;
    string model;
    bool is_engine_on;
    int current_speed;
    int current_gear;

  public:
    Manual_Car(string brand, string model){
        this->brand = brand;
        this->model = model;
        is_engine_on = false;
        current_speed = 0;
        current_gear = 0;
    }

    void start_engine(){
        is_engine_on = true;
        cout<<brand<<" "<<model<<" : Engine starts with a roar!"<<endl;
    }

    void stop_engine(){
        is_engine_on = false;
        current_speed = 0;
        cout<<brand<<" "<<model<<" : Engine turned off. "<<endl;
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

    void accelerate(int speed){
        if(!is_engine_on){
            cout<<brand<<" "<<model<<" : Engine is off! Cannot accelerate."<<endl;
            return;
        }
        current_speed += speed;
        cout<<brand<<" "<<model<<" : Accelerating to "<<current_speed<<" km/h"<<endl;
    }
    
    void brake(){
        current_speed -= 20;
        current_speed = max(current_speed , 0);
        cout<<brand<<" "<<model<<" : Braking! Speed is now "<<current_speed<<" km/h"<<endl;
    }
};

int main(){
    Manual_Car * my_manual_car = new Manual_Car("Suzuki", "WagonR");
    my_manual_car->start_engine();
    my_manual_car->shift_gear(1);
    my_manual_car->accelerate();
    my_manual_car->accelerate(40);
    my_manual_car->brake();
    my_manual_car->stop_engine();
    delete my_manual_car;

    

}