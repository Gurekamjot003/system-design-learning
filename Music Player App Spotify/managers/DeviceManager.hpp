#pragma once
#include "../factories/DeviceFactory.hpp"
using namespace std;

class DeviceManager{
private:
    IAudioOutputDevice* device;
    static DeviceManager* instance;

    DeviceManager(){
        device = NULL;
    }

public:
    static DeviceManager* get_instance(){
        if(!instance) instance = new DeviceManager();
        return instance;
    }

    void connect(DeviceType device_type){
        if(device) delete device;
        device = DeviceFactory::create_device(device_type);
        switch(device_type) {
            case DeviceType::BLUETOOTH:
                cout<< "Bluetooth device connected \n";
                break;
            case DeviceType::WIRED:
                cout<< "Wired device connected \n";
                break;
            case DeviceType::HEADPHONES:
                cout<< "Headphones connected \n";
        }
    }

    IAudioOutputDevice* get_device(){
        if(!device) throw runtime_error("No device connected.");
        return device;
    }

    bool has_output_device(){
        return device != NULL;
    }
};


DeviceManager* DeviceManager::instance = NULL;