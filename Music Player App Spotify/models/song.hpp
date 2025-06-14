#pragma once
#include<bits/stdc++.h>
using namespace std;

class Song{
private:
    string name;
    string artist;
    string path;

public:
    Song(string name, string artist, string path){
        this->name = name;
        this->artist = artist;
        this->path = path;
    }

    string get_name() const {
        return name;
    }

    string get_artist() const {
        return artist;
    }

    string get_path() const {
        return path;
    }
};