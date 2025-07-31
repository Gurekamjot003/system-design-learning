#include "scholars_mate_demo.hpp"

int main(){
    
    cout<<"Hello Chess!" << endl;
    ScholarsMateDemo demo;
    demo.run();

    cout<<"Enter player 1 name: ";
    string p1_name; cin>>p1_name;
    cout<<"Enter player 2 name: ";
    string p2_name; cin>>p2_name;

    GameManager* gm = GameManager::get_instance();

    User* p1 = new User("1", p1_name, nullptr);
    User* p2 = new User("2", p2_name, nullptr);

    gm->request_match(p1);
    string match_id = gm->request_match(p2);
    Match* match = gm->get_match_by_id(match_id);

    gm->display_active_matches();

    while(gm->get_match_by_id(match_id)->get_status() == GameStatus::IN_PROGRESS){
        cout << "\n--- " << gm->get_current_turn_player(match_id)->get_name() << "'s turn ---" << endl;
        cout << "Enter move (e.g., e2 e4): ";
        string from_str, to_str;
        cin >> from_str >> to_str;

        int from_row = 8 - (from_str[1] - '0');
        int from_col = from_str[0] - 'a';
        int to_row = 8 - (to_str[1] - '0');
        int to_col = to_str[0] - 'a';

        Position from(from_row, from_col);
        Position to(to_row, to_col);

        gm->make_move(match_id, from, to, gm->get_current_turn_player(match_id));
    }

    delete p1;
    delete p2;
    

    return 0;
}