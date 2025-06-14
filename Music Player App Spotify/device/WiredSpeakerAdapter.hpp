#pragma once
#include "IAudioOutputDevice.hpp"
#include "../external/WiredSpeakerAPI.hpp"
using namespace std;

class WiredSpeakerAdapter: public IAudioOutputDevice{
private:
    WiredSpeakerAPI* wired_api;

public:
    WiredSpeakerAdapter(WiredSpeakerAPI* wired_api){
        this->wired_api = wired_api;
    }
    void play_audio(Song* song) override{
        string payload = song->get_name() + " by " + song->get_artist();
        wired_api->play_sound_via_cable(payload);
    }
};