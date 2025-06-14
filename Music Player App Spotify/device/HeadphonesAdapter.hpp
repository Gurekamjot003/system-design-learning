#pragma once
#include "IAudioOutputDevice.hpp"
#include "../external/HeadphonesAPI.hpp"
using namespace std;

class HeadphonesAdapter: public IAudioOutputDevice{
private:
    HeadphonesAPI* headphone_api;

public:
    HeadphonesAdapter(HeadphonesAPI* headphones_api){
        this->headphone_api = headphone_api;
    }
    void play_audio(Song* song) override{
        string payload = song->get_name() + " by " + song->get_artist();
        headphone_api->play_sound_via_jack(payload);
    }
};