#pragma once
#include "user.hpp"
#include "game_status.hpp"

class Match: public ChatMediator{
private:
    string match_id;
    User* white_player, *black_player;
    Board* board;
    IChessRules* rules;
    GameStatus status;
    Color current_turn;
    vector<Move> move_history;
    vector<Message*> chat_history;

public:
    Match(string match_id, User* white_player, User* black_player, IChessRules* rules): match_id(match_id), white_player(white_player), black_player(black_player), rules(rules), status(GameStatus::IN_PROGRESS), current_turn(Color::WHITE) {
        this->board = new Board();
        white_player->set_mediator(this);
        black_player->set_mediator(this);
        cout << "Match created: " << match_id << endl;
        cout << "White Player: " << white_player->get_name() << endl;
        cout << "Black Player: " << black_player->get_name() << endl;
    }

    ~Match() {
        delete board;
        for (Message* msg : chat_history) {
            delete msg;
        }
        delete rules;
    }

    Color get_current_turn_color(){
        return current_turn;
    }

    bool make_move(Position from, Position to, User* player){
        if(status != GameStatus::IN_PROGRESS){
            cout<<"Game is not in progress"<<endl;
            return false;
        }


        Color player_color = get_player_color(player);
        if(player_color != current_turn){
            cout<<"It is not your turn"<<endl;
            return false;
        }

        Piece* piece = board->get_piece(from);
        if(!piece or piece->get_color() != player_color){
            cout<<"Invalid move"<<endl;
            return false;
        }

        Move move(from, to, piece, board->get_piece(to));

        if(!rules->is_valid_move(move, board)){
            cout<<"Invalid move"<<endl;
            return false;
        }

        board->move_piece(from, to);
        move_history.push_back(move);

        cout<<"Piece moved from " << from.to_algebraic_notation() << " to " << to.to_algebraic_notation() << endl;
        board->display();

        if(rules->is_in_check(get_opposite_color(current_turn), board)){
            if(rules->is_check_mate(get_opposite_color(current_turn), board)){
                cout<<"Checkmate!"<<endl;
                cout<<player->get_name()<<" wins!"<<endl;
                status = GameStatus::COMPLETED;
                return true;
            }
            cout<<"Check!"<<endl;
        } else if (rules->is_stale_mate(get_opposite_color(current_turn), board)) {
            cout << "Stalemate!" << endl;
            status = GameStatus::COMPLETED;
            return true;
        }

        current_turn = get_opposite_color(current_turn);
        return true;
    }

    Color get_opposite_color(Color color){
        return color == Color::WHITE ? Color::BLACK : Color::WHITE;
    }

    void quit_game(User* player){
        if(player == white_player){            
            cout << white_player->get_name() << " resigned. " << black_player->get_name() << " wins!" << endl;
            
            settle_score(black_player, white_player);

        } else if (player == black_player){
            cout << black_player->get_name() << " resigned. " << white_player->get_name() << " wins!" << endl;
            
            settle_score(white_player, black_player);

        }
        status = GameStatus::COMPLETED;
    
    }

    void settle_score(User* winner, User* loser){
        int rating_difference = winner->get_score() - loser->get_score();

        int k_factor = 32; // Elo K-factor
        double expected_score_winner = 1.0 / (1.0 + pow(10, (double)rating_difference / 400.0));
        double expected_score_loser = 1.0 / (1.0 + pow(10, (double)-rating_difference / 400.0));

        int new_score_winner = winner->get_score() + k_factor * (1 - expected_score_winner);
        int new_score_loser = loser->get_score() + k_factor * (0 - expected_score_loser);

        winner->increment_score(new_score_winner - winner->get_score());
        loser->decrement_score(loser->get_score() - new_score_loser);

        cout << winner->get_name() << "'s new score: " << winner->get_score() << endl;
        cout << loser->get_name() << "'s new score: " << loser->get_score() << endl;
    }

    void end_game(User* winner, string reason){
        cout << winner->get_name() << " wins by " << reason << "!" << endl;
        status = GameStatus::COMPLETED;

        settle_score(winner, (winner == white_player ? black_player : white_player));
    }

    Color get_player_color(User* player){
        return player == white_player ? Color::WHITE : Color::BLACK;
    }

    User* get_player_by_color(Color color){
        return color == Color::WHITE ? white_player : black_player;
    }

    void send_message(Message message) override {
        chat_history.push_back(new Message(message.get_sender_id(), message.get_content()));
        white_player->receive_message(&message);
        black_player->receive_message(&message);
    }

    void add_user(User* user) override {
        // Users are added during match creation
    }

    void remove_user(User* user){
        quit_game(user);
    }

    string get_match_id() const {
        return match_id;
    }

    GameStatus get_status() const {
        return status;
    }

    User* get_white_player() const {
        return white_player;
    }

    User* get_black_player() const {
        return black_player;
    }

    Board* get_board() const {
        return board;
    }
};