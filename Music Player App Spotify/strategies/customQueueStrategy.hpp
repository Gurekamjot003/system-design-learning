#pragma once
#include<bits/stdc++.h>
#include "PlayStrategy.hpp"
using namespace std;

class CustomQueueStrategy : public PlayStrategy {
private:
    Playlist* playlist;
    int index;
    queue<Song*> next_queue;
    stack<Song*> prev_stack;

public:
    CustomQueueStrategy(){
        playlist = NULL;
        index = -1;
    }

    void set_playlist(Playlist* playlist) override{
        this->playlist = playlist;
        if(!playlist or playlist->get_song_count() == 0) return;
        index = -1;
        while(!next_queue.empty()) next_queue.pop();
        while(!prev_stack.empty()) prev_stack.pop();
    }

    bool has_next() override {
        return playlist && (index + 1)<playlist->get_song_count();
    }

    Song* next() override{
        if(!next_queue.empty()){
            Song* song = next_queue.front();
            next_queue.pop();
            prev_stack.push(song);
            vector<Song*> songs = playlist->get_songs();
            for(int i = 0; i<songs.size(); i++){
                if(songs[i] == song){
                    index = i;
                    break;
                }
            }
            return song;
        }

        if(!has_next()){
            throw runtime_error("No playlist set or no next song available.");
        }

        
        index = index + 1;
        Song* song = playlist->get_songs()[index];
        prev_stack.push(song);
        return song;
    }

    bool has_previous() override{
        return playlist && (index-1) >=0;
    }

    Song* previous() override{
        if(!prev_stack.empty()){
            Song* song = prev_stack.top();
            prev_stack.pop();
            vector<Song*> songs = playlist->get_songs();
            for(int i = 0; i<songs.size(); i++){
                if(songs[i] == song){
                    index = i;
                    break;
                }
            }
            return song;
        }
        if(!has_previous()){
            throw runtime_error("No playlist set or no previous song available.");
        }
        index--;
        Song* song = playlist->get_songs()[index];
        
        return song;
    }

    void add_to_next(Song* song) override{
        if(!song){
            throw runtime_error("Cannot enqueue a null song.");
        }
        next_queue.push(song);
    }

};