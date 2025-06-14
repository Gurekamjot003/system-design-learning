#pragma once
#include "MusicPlayerFacade.hpp"
using namespace std;

class MusicPlayerApplication{
private:
    vector<Song*> songs;
    static MusicPlayerApplication* instance;

    MusicPlayerApplication(){}

public:
    static MusicPlayerApplication* get_instance(){
        if(!instance) instance = new MusicPlayerApplication();
        return instance;
    }

    void create_song_in_library(string name, string artist, string path){
        songs.push_back(new Song(name, artist, path));
    }

    void create_playlist(string name){
        PlaylistManager::get_instance()->create_playlist(name);
    }

    Song* find_song_by_title(string title){
        for(auto& song: songs){
            if(song->get_name() == title) return song;
        }
        return NULL;
    }

    void add_song_to_playlist(string playlist_name, string song_name){
        Song* song = find_song_by_title(song_name);
        PlaylistManager::get_instance()->add_song_to_playlist(playlist_name, song);
    }

    void connect_audio_device(DeviceType device){
        DeviceManager::get_instance()->connect(device);
    }

    void select_play_strategy(PlayStrategyType play_strategy){
        MusicPlayerFacade::get_instance()->set_strategy(play_strategy);
    }

    void load_playlist(string playlist_name){
        MusicPlayerFacade::get_instance()->load_playlist(playlist_name);
    }

    void play_single_song(string song_name){
        Song* song = find_song_by_title(song_name);
        MusicPlayerFacade::get_instance()->play_song(song);
    }

    void pause_current_song(string song_name){
        Song* song = find_song_by_title(song_name);
        MusicPlayerFacade::get_instance()->pause_song(song);
    }

    void play_all_tracks_in_playlist(){
        MusicPlayerFacade::get_instance()->play_all_tracks();
    }

    void play_previous_track_in_playlist(){
        MusicPlayerFacade::get_instance()->play_previous_track();
    }

    void queue_next_song(string song_name){
        Song* song = find_song_by_title(song_name);
        MusicPlayerFacade::get_instance()->enqueue_next(song);
    }
};

MusicPlayerApplication* MusicPlayerApplication::instance = NULL;