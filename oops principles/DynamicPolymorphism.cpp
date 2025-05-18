#include<bits/stdc++.h>
using namespace std;

class Car{
  protected:
    string brand;
    string model;
    bool is_engine_on;
    int current_speed;

  public:
    Car(string brand, string model){
        this->brand = brand;
        this->model = model;
        is_engine_on = false;
        current_speed = 0;
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
    
    virtual void accelerate() = 0;
    
    virtual void brake() = 0;
    
    

    virtual ~Car() {}
};

class Manual_Car : public Car{
  private:
    int current_gear;
  
  public:
    Manual_Car(string brand, string model) : Car(brand, model){
        current_gear = 0;
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
};

class Electric_Car : public Car{
  private:
    int battery_level;

  public:
    Electric_Car(string brand, string model) : Car(brand, model){
        battery_level = 100;
    }

    void charge_battery(){
        battery_level = 100;
        cout<<brand<<" "<<model<<" : Battery fully charged!"<<endl;
    }

    void accelerate(){
        if(!is_engine_on){
            cout<<brand<<" "<<model<<" : Engine is off! Cannot accelerate."<<endl;
            return;
        }
        if(battery_level<=0){
            cout<<brand<<" "<<model<<" : Battery dead! Cannot accelerate."<<endl;
            return;
        }
        current_speed += 15;
        battery_level -= 10;
        battery_level = max(0, battery_level);
        cout<<brand<<" "<<model<<" : Accelerating to "<<current_speed<<" km/h. Battery at "<<battery_level<<"%."<<endl;
    }
    
    void brake(){
        current_speed -= 15;
        current_speed = max(current_speed , 0);
        battery_level += 5;
        battery_level = min(battery_level, 100);
        cout<<brand<<" "<<model<<" : Regenerative Braking! Speed is now "<<current_speed<<" km/h. Battery at "<<battery_level<<"%."<<endl;
    }
};

int main(){
    Manual_Car * my_manual_car = new Manual_Car("Suzuki", "WagonR");
    my_manual_car->start_engine();
    my_manual_car->shift_gear(1);
    my_manual_car->accelerate();
    my_manual_car->accelerate();
    my_manual_car->brake();
    my_manual_car->stop_engine();
    delete my_manual_car;

    cout<<"-------------------------"<<endl;

    Electric_Car * my_electric_car = new Electric_Car("Tesla", "Model S");
    my_electric_car->start_engine();
    my_electric_car->accelerate();
    my_electric_car->accelerate();
    my_electric_car->brake();
    my_electric_car->stop_engine();
    delete my_electric_car;

}