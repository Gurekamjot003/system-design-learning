#pragma once
#include "../device/IAudioOutputDevice.hpp"
#include "../device/BluetoothSpeakerAdapter.hpp"
#include "../device/WiredSpeakerAdapter.hpp"
#include "../device/HeadphonesAdapter.hpp"
#include "../enums/DeviceType.hpp"
using namespace std;

class DeviceFactory{
public:
    static IAudioOutputDevice* create_device(DeviceType device_type){
        switch(device_type){
            case(DeviceType::BLUETOOTH):
                return new BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
            case(DeviceType::HEADPHONES):
                return new HeadphonesAdapter(new HeadphonesAPI());
            case(DeviceType::WIRED):
                return new WiredSpeakerAdapter(new WiredSpeakerAPI());
            default:
                throw invalid_argument("Invalid device type.");
        }
    }
};