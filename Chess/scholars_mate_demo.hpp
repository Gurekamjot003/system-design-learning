#pragma once
#include "Core/game_manager.hpp"

class ScholarsMateDemo{
public: 
    void run(){
        GameManager* gm = GameManager::get_instance();

        User* gurekam = new User("1", "Gurekam", nullptr);
        User* vt = new User("2", "VT", nullptr);

        gm->request_match(vt);
        string match_id = gm->request_match(gurekam);

        gm->display_active_matches();

        User* white_player = gm->get_match_by_id(match_id)->get_white_player();
        User* black_player = gm->get_match_by_id(match_id)->get_black_player();


        // Scholar's Mate moves
        // 1. e4 e5
        cout << "\n--- 1. e4 ---" << endl;
        gm->make_move(match_id, Position(6, 4), Position(4, 4), white_player); // e4
        cout << "\n--- 1... e5 ---" << endl;
        gm->make_move(match_id, Position(1, 4), Position(3, 4), black_player); // e5

        // 2. Qh5 Nc6
        cout << "\n--- 2. Qh5 ---" << endl;
        gm->make_move(match_id, Position(7, 3), Position(3, 7), white_player); // Qh5
        cout << "\n--- 2... Nc6 ---" << endl;
        gm->make_move(match_id, Position(0, 1), Position(2, 2), black_player); // Nc6

        // 3. Bc4 Nf6
        cout << "\n--- 3. Bc4 ---" << endl;
        gm->make_move(match_id, Position(7, 5), Position(4, 2), white_player); // Bc4
        cout << "\n--- 3... Nf6 ---" << endl;
        gm->make_move(match_id, Position(0, 6), Position(2, 5), black_player); // Nf6

        // 4. Qxf7#
        cout << "\n--- 4. Qxf7# ---" << endl;
        gm->make_move(match_id, Position(3, 7), Position(1, 5), white_player); //
        gm->make_move(match_id, Position(3, 7), Position(1, 5), white_player); // Qxf7#

        gm->display_active_matches();

        delete white_player;
        delete black_player;
    }
    
};