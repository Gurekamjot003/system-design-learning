#pragma once
#include "../Board/board.hpp"
#include "../notification system/console_notifier.hpp"
#include "../Rules/standard_rules.hpp"
#include "../Board/dice.hpp"
#include "../Board/player.hpp"

class Game{
    Board* board;
    deque<Player*> players;
    Dice* dice;
    IRules* rules;
    vector<IObserver*> observers;
    bool is_game_over;

public:
    Game(Board* board, Dice* dice, IRules* rules)
        : board(board), dice(dice), rules(rules), is_game_over(false) {
        if (!board || !dice || !rules) {
            throw invalid_argument("Board, Dice, and Rules cannot be null");
        }
    }
    Board* get_board() const {
        return board;
    }
    void add_player(Player* player) {
        if (!player) {
            throw invalid_argument("Player cannot be null");
        }
        players.push_back(player);
    }

    void add_observer(IObserver* observer) {
        if (!observer) {
            throw invalid_argument("Observer cannot be null");
        }
        observers.push_back(observer);
    }

    void notify_observers(const string& message) {
        for (auto& observer : observers) {
            observer->update(const_cast<string&>(message));
        }
    }

    void display_player_positions(){
        cout << "Current Player Positions:" << endl;
        for (const auto& player : players) {
            player->display();
        }
    }

    void play(){
        if(players.size()<2) {
            throw invalid_argument("At least two players are required to start the game");
        }

        notify_observers("Game started!");

        while (!is_game_over) {
            auto player = players.front();
            players.pop_front(); // Get the current player
            players.push_back(player); // Move the player to the back of the queue

            cout<< "\n\nCurrent Player: " << player->getName() << endl;
            cout<<"Click Enter to roll the dice...";
            cin.get(); // Wait for user input to roll the dice

            int dice_value = dice->roll();
            cout << player->getName() << " rolled a " << dice_value << endl;

            int cur_pos = player->getPosition();

            if (rules->is_valid_move(player->getPosition(), dice_value, board->get_size())) {

                int intermediate_position = player->getPosition() + dice_value;
                
                if(board->get_entity_at(intermediate_position)) {
                    cout << player->getName() << " encountered a " 
                    << board->get_entity_at(intermediate_position)->name() 
                    << " at position " << intermediate_position << endl;
                    notify_observers(player->getName() + " encountered a " 
                        + board->get_entity_at(intermediate_position)->name() 
                        + " at position " + to_string(intermediate_position));
                }
                
                int new_position = rules->calculate_new_position(player->getPosition(), dice_value, board);
                player->setPosition(new_position);
                cout << player->getName() << " moved to position " << new_position << endl;

                notify_observers(player->getName() + " moved to position " + to_string(new_position));
                display_player_positions();

                if (rules->check_winner(new_position, board->get_size())) {
                    cout << player->getName() << " wins!" << endl;
                    notify_observers(player->getName() + " wins the game!");
                    is_game_over = true;
                }

               
            } else {
                cout << player->getName() << " cannot move to position " 
                     << player->getPosition() + dice_value << endl;
            }
            

        }


    }
    ~Game() {
        delete board; // Assuming board is dynamically allocated
        delete dice; // Assuming dice is dynamically allocated
        delete rules; // Assuming rules is dynamically allocated
        for (auto& player : players) {
            delete player; // Clean up dynamically allocated players
        }
        for (auto& observer : observers) {
            delete observer; // Clean up dynamically allocated observers
        }
    }
};