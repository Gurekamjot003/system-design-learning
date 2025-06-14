#pragma once
#include "../models/song.hpp"

class IAudioOutputDevice{
public:
    virtual void play_audio(Song* song) = 0;
    virtual ~IAudioOutputDevice(){}
};