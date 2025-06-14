#pragma once
#include "managers/StrategyManager.hpp"
#include "managers/PlaylistManager.hpp"
#include "core/AudioEngine.hpp"
#include "managers/DeviceManager.hpp"
using namespace std;

class MusicPlayerFacade{
private:
    AudioEngine* engine;
    Playlist* current_playlist;
    PlayStrategy* strategy;
    static MusicPlayerFacade* instance;

    MusicPlayerFacade(){
        engine = new AudioEngine();
        current_playlist = NULL;
        strategy = NULL;
    }
public:
    static MusicPlayerFacade* get_instance(){
        if(!instance) instance = new MusicPlayerFacade();
        return instance;
    }

    void connect_device(DeviceType device_type){
        DeviceManager::get_instance()->connect(device_type);
    }

    void set_strategy(PlayStrategyType strategy_type){
        this->strategy = StrategyManager::get_instance()->get_strategy(strategy_type);
    }

    void load_playlist(string name){
        current_playlist = PlaylistManager::get_instance()->get_playlist(name);
        if(!strategy) throw runtime_error("Play strategy not set before loading.");
        strategy->set_playlist(current_playlist);
    }

    void play_song(Song* song){
        if(!DeviceManager::get_instance()->has_output_device())
            throw runtime_error("No output device connnected.");
        IAudioOutputDevice* device = DeviceManager::get_instance()->get_device();
        engine->play(device, song);
    }

    void pause_song(Song* song){
        if(song->get_name() != engine->get_current_song_name()){
            throw runtime_error("Cannot pause a song not being played.");
        }
        engine->pause();
    }

    void play_all_tracks(){
        if(!current_playlist) throw runtime_error("No playlist loaded.");

        while (strategy->has_next())
        {
            Song* next_song = strategy->next();
            IAudioOutputDevice* device = DeviceManager::get_instance()->get_device();
            engine->play(device, next_song);
        }
        cout<<"Completed playlist: "<<current_playlist->get_name()<<endl;
    }
    
    void play_next_track(){
        if(!current_playlist) throw runtime_error("No playlist loaded.");
        
        if (strategy->has_next())
        {
            Song* next_song = strategy->next();
            IAudioOutputDevice* device = DeviceManager::get_instance()->get_device();
            engine->play(device, next_song);
        }
        else{
            cout<<"Completed playlist: "<<current_playlist->get_name()<<endl;
        }
    }
    
    void play_previous_track(){
        if(!current_playlist) throw runtime_error("No playlist loaded.");
        
        if (strategy->has_previous())
        {
            Song* prev_song = strategy->previous();
            IAudioOutputDevice* device = DeviceManager::get_instance()->get_device();
            engine->play(device, prev_song);
        }
        else{
            cout<<"Completed playlist: "<<current_playlist->get_name()<<endl;
        }
    }

    void enqueue_next(Song* song){
        strategy->add_to_next(song);
    }
};

MusicPlayerFacade* MusicPlayerFacade::instance = NULL;