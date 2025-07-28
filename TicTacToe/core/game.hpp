#pragma once
#include "board.hpp"
#include "../Rules/standard_rules.hpp"
#include "../Player/player.hpp"
#include "../Notification system/console_notifier.hpp"

class Game{
    Board* board;
    IRules* rules;
    deque<Player*> players;
    vector<IObserver*> observers;
    bool game_over = false;

public:
    Game(int board_size, Symbol empty_symbol, IRules* rules) : rules(rules) {
        board = new Board(board_size, empty_symbol);
    }
    void add_player(Player* player) {
        players.push_back(player);
    }
    void add_observer(IObserver* observer) {
        observers.push_back(observer);
    }
    void notify_observers(string msg) {
        for(auto& observer : observers) {
            observer->update(msg);
        }
    }
    void play(){

        while(!game_over){
            Player* current_player = players.front();
            players.pop_front();
            cout << current_player->get_name() << "'s turn. Enter row and column: ";
            int row, col;
            cin >> row >> col;
            if(rules->is_valid_move(board, row, col)) {
                board->place_mark(row, col, current_player->get_symbol());
                board->display();
                if(rules->is_winner(board, row, col)) {
                    cout << current_player->get_name() << " wins!" << endl;
                    current_player->increment_score();
                    notify_observers(current_player->get_name() + " wins!");
                    game_over = true;
                } else if(rules->is_draw(board)) {
                    cout << "It's a draw!" << endl;
                    notify_observers("It's a draw!");
                    game_over = true;
                } else {
                    players.push_back(current_player);
                }
            } else {
                cout << "Invalid move. Try again." << endl;
                players.push_front(current_player);
            }
        }
    }

    void display_board() {
        board->display();
    }
    ~Game() {
        delete board;
        delete rules;
        for(auto& player : players) {
            delete player;
        }
        for(auto& observer : observers) {
            delete observer;
        }
    }

    void reset() {
        delete board;
        board = new Board(board->get_size(), board->get_empty_symbol());
        game_over = false;
        notify_observers("Game has been reset.");
    }
};