#include<bits/stdc++.h>
using namespace std;

class ICommand{
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand(){}
};

class Light{
public:
    void on(){
        cout<<"Light is ON"<<endl;
    }
    
    void off(){
        cout<<"Light is OFF"<<endl;
    }
};

class Fan{
public:
    void on(){
        cout<<"Fan is ON"<<endl;
    }

    void off(){
        cout<<"Fan is OFF"<<endl;
    }
};

class LightCommand: public ICommand{
private:
    Light* light;

public:
    LightCommand(Light* light){
        this->light = light;
    }

    void execute(){
        light->on();
    }

    void undo(){
        light->off();
    }
};

class FanCommand: public ICommand{
private:
    Fan* fan;

public:
    FanCommand(Fan* fan){
        this->fan = fan;
    }

    void execute(){
        fan->on();
    }

    void undo(){
        fan->off();
    }
};

class RemoteController{
private:
    int num_buttons;
    vector<ICommand*> buttons;
    vector<bool> button_pressed;

public:
    RemoteController(int num_buttons){
        this->num_buttons = num_buttons;
        buttons.resize(num_buttons, NULL);
        button_pressed.resize(num_buttons, false);
    }

    void set_command(int i, ICommand* command){
        if(i<0 or i>=num_buttons) return;
        if(buttons[i]) delete buttons[i];
        buttons[i] = command;
        button_pressed[i] = false;
    }

    void press_button(int i){
        if(i<0 or i>= num_buttons) return;
        if(!buttons[i]){
            cout<<"This button has no command assigned to it."<<endl;
            return;
        }
        button_pressed[i]? buttons[i]->undo(): buttons[i]->execute();
        button_pressed[i] = !button_pressed[i];
    }

    ~RemoteController(){
        for(int i = 0; i<num_buttons; i++){
            if(buttons[i]) delete buttons[i];
        }
    }
};

int main(){
    Light* tubelight = new Light();
    Fan* ceiling_fan = new Fan();

    RemoteController* remote = new RemoteController(4);

    remote->set_command(0, new LightCommand(tubelight));
    remote->set_command(1, new FanCommand(ceiling_fan));

    remote->press_button(0);
    remote->press_button(0);

    remote->press_button(1);
    remote->press_button(1);

    remote->press_button(2);

    delete remote;
    delete tubelight;
    delete ceiling_fan;
}