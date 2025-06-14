#pragma once
#include<bits/stdc++.h>
#include "PlayStrategy.hpp"
using namespace std;

class RandomPlayStrategy : public PlayStrategy {
private:
    Playlist* playlist;
    vector<Song*> remaining_songs;
    stack<Song*> history;

public:
    RandomPlayStrategy(){
        playlist = NULL;
    }

    void set_playlist(Playlist* playlist) override{
        this->playlist = playlist;
        if(!playlist or playlist->get_song_count() == 0) return;

        remaining_songs = playlist->get_songs();
        history = stack<Song*>();

    }

    bool has_next() override {
        return playlist && !remaining_songs.empty();
    }

    Song* next() override{
        if(!has_next()){
            throw runtime_error("No playlist set or no next song available.");
        }
        int index = rand()%remaining_songs.size();
        swap(remaining_songs[index], remaining_songs.back());
        Song* song = remaining_songs.back();
        remaining_songs.pop_back();
        history.push(song);
        return song;
    }

    bool has_previous() override{
        return playlist && !history.empty();
    }

    Song* previous() override{
        if(!has_previous()){
            throw runtime_error("No playlist set or no previous song available.");
        }
        
        Song* song = history.top();
        history.pop();
        return song;
    }

};