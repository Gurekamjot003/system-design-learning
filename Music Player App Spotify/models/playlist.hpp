#pragma once
#include<bits/stdc++.h>
#include "song.hpp"
using namespace std;

class Playlist {
private:
    string name;
    vector<Song*> songs;

public:
    Playlist(string name){
        this->name = name;
    }

    void add_song(Song* song){
        if(!song){
            throw runtime_error("Cannot add a null song to the playlist.");
        }
        songs.push_back(song);
    }

    string get_name(){
        return name;
    }

    vector<Song*> get_songs(){
        return songs;
    }

    int get_song_count(){
        return songs.size();
    }
};
