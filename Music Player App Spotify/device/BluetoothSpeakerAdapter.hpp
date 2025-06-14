#pragma once
#include "IAudioOutputDevice.hpp"
#include "../external/BluetoothSpeakerAPI.hpp"
using namespace std;

class BluetoothSpeakerAdapter: public IAudioOutputDevice{
private:
    BluetoothSpeakerAPI* bluetooth_api;

public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* bluetooth_api){
        this->bluetooth_api = bluetooth_api;
    }
    void play_audio(Song* song) override{
        string payload = song->get_name() + " by " + song->get_artist();
        bluetooth_api->play_sound_via_bluetooth(payload);
    }
};