#pragma once
#include "score_based_matching.hpp"

class GameManager{
private:
    static GameManager* instance;
    map<string, Match*> active_matches;
    vector<User*> waiting_users;
    MatchingStrategy* matching_strategy;
    long long match_counter;

    GameManager(){
        matching_strategy = new ScoreBasedMatching(100);
        match_counter = 0;
    }

public:

    ~GameManager(){
        for (auto& pair : active_matches) {
            delete pair.second;
        }
        delete matching_strategy;
    }

    static GameManager* get_instance(){
        if(!instance) instance = new GameManager();
        return instance;
    }

    string request_match(User* user){
        cout<<user->get_name() << " requested a match." << endl;
        
        User* match_user = matching_strategy->find_match(user, waiting_users);
        if(match_user){
            cout<<user->get_name() << " and " << match_user->get_name() << " found a match." << endl;
            matching_strategy->remove_user_from_queue(match_user, waiting_users);

            string match_id = "match" + to_string(match_counter++);
            Match* match = new Match(match_id, user, match_user, new StandardChessRules());
            active_matches[match_id] = match;
            match->get_board()->display(Color::WHITE);
            return match_id;
        }
        
        cout<<user->get_name() << " added to the waiting queue." << endl;
        matching_strategy->add_user_to_queue(user, waiting_users);
        
        return "";
    }   

    void make_move(string match_id, Position from, Position to, User* player){
        if(!active_matches.count(match_id)) return;
        Match* match = active_matches[match_id];
        
        match->make_move(from, to, player);
        if(match->get_status() == GameStatus::COMPLETED){
            active_matches.erase(match_id);
            delete match;
            cout<<"Match " << match_id << " completed." << endl;
        }
    }

    void quit_match(string match_id, User* player){
        if(!active_matches.count(match_id)) return;

        Match* match = active_matches[match_id];

        match->quit_game(player);
        active_matches.erase(match_id);
        delete match;
        cout<<"Match " << match_id << " quit." << endl;
    }

    void send_chat_msg(string match_id, string message, User* player){
        if(!active_matches.count(match_id)) return;

        Match* match = active_matches[match_id];

        match->send_message(Message(player->get_id(), message));
    }

    Match* get_match_by_id(string match_id){
        if(active_matches.count(match_id))
            return active_matches[match_id];
        return nullptr;
    }

    void display_active_matches(){
        cout<<"\nActive Matches:"<<active_matches.size()<<endl;
        for (const auto& pair : active_matches) {
            cout << "Match ID: " << pair.first << endl;
            cout << "White Player: " << pair.second->get_white_player()->get_name() << endl;
            cout << "Black Player: " << pair.second->get_black_player()->get_name() << endl;
            cout<<endl;
        }
        cout<<"Total Active Matches: " << active_matches.size() << endl;
        cout<<"Users waiting: "<<waiting_users.size() << endl;
    }

    User* get_current_turn_player(string match_id){
        Match* match = get_match_by_id(match_id);
        if(!match) throw runtime_error("Match not found");

        return match->get_current_turn_color() == Color::WHITE? match->get_white_player(): match->get_black_player();
    }
    
};

GameManager* GameManager::instance = nullptr;