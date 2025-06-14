#pragma once
#include "../device/IAudioOutputDevice.hpp"
#include<bits/stdc++.h>

using namespace std;

class AudioEngine{
private:
    Song* cur_song;
    bool is_song_paused;

public:

    AudioEngine(){
        cur_song = NULL;
        is_song_paused = false;
    }   

    void play(IAudioOutputDevice* device, Song* song){
        if(!song) throw runtime_error("Cannot play a null song.");
        
        if(is_song_paused && song == cur_song){
            is_song_paused = false;
            cout<<"Resuming song: "<<song->get_name()<<endl;
            device->play_audio(song);
            return;
        }

        cur_song = song;
        is_song_paused = false;
        cout<<"Playing song: "<<song->get_name()<<endl;
        device->play_audio(song);
    }

    string get_current_song_name(){
        if(cur_song)
            return cur_song->get_name();
        return "";
    }

    bool is_paused(){
        return is_song_paused;
    }

    void pause(){
        if(!cur_song) throw runtime_error("No song being played currrently.");
        if(is_song_paused) throw runtime_error("Song already paused.");
        is_song_paused = true;
        cout<<"Pausing song: "<<cur_song->get_name()<<endl;
    }
};