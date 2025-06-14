#include "MusicPlayerApplication.hpp"
using namespace std;

int main(){
    try{
        auto application = MusicPlayerApplication::get_instance();

        application->create_song_in_library("Kesariya", "Arijit Singh", "/music/kesariya.mp3");
        application->create_song_in_library("Tum Hi Ho", "Arijit Singh", "/music/tum_hi_ho.mp3");
        application->create_song_in_library("Blinding Lights", "The Weeknd", "/music/blinding_lights.mp3");
        application->create_song_in_library("Apna Bana Le", "Arijit Singh", "/music/apna_bana_le.mp3");
        application->create_song_in_library("Shape of You", "Ed Sheeran", "/music/shape_of_you.mp3");
        application->create_song_in_library("Chaleya", "Arijit Singh", "/music/chaleya.mp3");
        application->create_song_in_library("Perfect", "Ed Sheeran", "/music/perfect.mp3");
        application->create_song_in_library("Raataan Lambiyan", "Jubin Nautiyal", "/music/raataan_lambiyan.mp3");
        application->create_song_in_library("Love Me Like You Do", "Ellie Goulding", "/music/love_me_like_you_do.mp3");
        application->create_song_in_library("Phir Aur Kya Chahiye", "Arijit Singh", "/music/phir_aur_kya_chahiye.mp3");
        application->create_song_in_library("Night Changes", "One Direction", "/music/night_changes.mp3");

        application->create_playlist("Gurekam Bollywood");
        application->add_song_to_playlist("Gurekam Bollywood", "Kesariya");
        application->add_song_to_playlist("Gurekam Bollywood", "Tum Hi Ho");
        application->add_song_to_playlist("Gurekam Bollywood", "Phir Aur Kya Chahiye");
        application->add_song_to_playlist("Gurekam Bollywood", "Raataan Lambiyan");
        application->add_song_to_playlist("Gurekam Bollywood", "Chaleya");
        application->add_song_to_playlist("Gurekam Bollywood", "Apna Bana Le");

        application->connect_audio_device(DeviceType::BLUETOOTH);

        cout<<"\nNormal pause play song"<<endl;
        application->play_single_song("Night Changes");
        application->pause_current_song("Night Changes");
        application->play_single_song("Night Changes");

        cout<<"\nSequential play"<<endl;
        application->select_play_strategy(PlayStrategyType::SEQUENTIAL);
        application->load_playlist("Gurekam Bollywood");
        application->play_all_tracks_in_playlist();

        cout<<"\nRandom play"<<endl;
        application->select_play_strategy(PlayStrategyType::RANDOM);
        application->load_playlist("Gurekam Bollywood");
        application->play_all_tracks_in_playlist();

        cout<<"\nCustom queue"<<endl;
        application->select_play_strategy(PlayStrategyType::CUSTOM_QUEUE);
        application->load_playlist("Gurekam Bollywood");
        application->queue_next_song("Kesariya");
        application->queue_next_song("Raataan Lambiyan");
        application->play_all_tracks_in_playlist();

        cout<<"\nPlaying previous"<<endl;
        application->select_play_strategy(PlayStrategyType::RANDOM);
        application->load_playlist("Gurekam Bollywood");
        application->play_all_tracks_in_playlist();

        application->play_previous_track_in_playlist();
        application->play_previous_track_in_playlist();
    }
    catch(exception e){
        cerr<<"Error: "<<e.what()<<endl;
    }
}