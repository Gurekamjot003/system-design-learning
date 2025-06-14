#pragma once
#include <bits/stdc++.h>
#include "../models/playlist.hpp"
using namespace std;

class PlaylistManager{
private:
    static PlaylistManager* instance;
    unordered_map<string, Playlist*> playlists;
    PlaylistManager(){}

public:
    static PlaylistManager* get_instance(){
        if(!instance){
            instance = new PlaylistManager(); 
        }
        return instance;
    }

    void create_playlist(string name){
        if(playlists.find(name) != playlists.end()){
            throw runtime_error("Playlist " + name + " already exists.");
        }
        playlists[name] = new Playlist(name);
    }

    void add_song_to_playlist(string playlist_name, Song* song){
        if(playlists.find(playlist_name) == playlists.end()){
            throw runtime_error("Playlist " + playlist_name + " does not exist.");
        }
        playlists[playlist_name]->add_song(song);
    }

    Playlist* get_playlist(string name){
        if(playlists.find(name) == playlists.end()){
            throw runtime_error("Playlist " + name + " doest not exist.");
        }
        return playlists[name];
    }
};

PlaylistManager* PlaylistManager::instance = NULL;