#pragma once
#include<bits/stdc++.h>
#include "PlayStrategy.hpp"
using namespace std;

class SequentialPlayStrategy : public PlayStrategy {
private:
    Playlist* playlist;
    int index;

public:
    SequentialPlayStrategy(){
        playlist = NULL;
        index = -1;
    }

    void set_playlist(Playlist* playlist) override{
        this->playlist = playlist;
        index = -1;
    }

    bool has_next() override {
        return playlist && index + 1 < playlist->get_song_count();
    }

    Song* next() override{
        if(!has_next()){
            throw runtime_error("No playlist set or no next song available.");
        }
        index++;
        return playlist->get_songs()[index];
    }

    bool has_previous() override{
        return playlist && index-1>=0;
    }

    Song* previous() override{
        if(!has_previous()){
            throw runtime_error("No playlist set or no previous song available.");
        }
        index--;
        return playlist->get_songs()[index];
    }

};