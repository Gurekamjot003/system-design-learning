#pragma once
#include <bits/stdc++.h>
#include "../models/playlist.hpp"
#include "../models/song.hpp"
using namespace std;

class PlayStrategy{
public:
    virtual void set_playlist(Playlist* playlist) = 0;
    virtual bool has_next() = 0;
    virtual Song* next() = 0;
    virtual bool has_previous() = 0;
    virtual Song* previous() = 0;
    virtual void add_to_next(Song* song){};
    virtual ~PlayStrategy() {}
};