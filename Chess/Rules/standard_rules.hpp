#pragma once
#include "i_chess_rules.hpp"

class StandardChessRules: public IChessRules{
    
public:
    bool is_valid_move(const Move& move, Board* board) override{
        Piece* piece = move.get_piece();
        if (piece == nullptr) {
            return false; // No piece to move
        }

        // For now, we just check if the move is valid for the piece itself
        vector<Position> possible_moves = piece->get_possible_moves(move.get_from(), board);
        for (const Position& p : possible_moves) {
            if (p == move.get_to()) {
                return !would_move_cause_check(move, board, piece->get_color());
            }
        }
        return false;
    }

    bool is_in_check(Color king_color, Board* board) override{
        Position king_pos = board->find_king(king_color);
        if(king_pos.get_row() == -1) return false;

        Color opponent_color = (king_color == Color::WHITE) ? Color::BLACK : Color::WHITE;

        vector<Position> opponent_pieces = board->get_all_pieces_of_color(opponent_color);
        for (const Position& pos : opponent_pieces){
            Piece* piece = board->get_piece(pos);
            vector<Position> possible_moves = piece->get_possible_moves(pos, board);
            for (const Position& p : possible_moves) {
                if (p == king_pos) {
                    return true;
                }
            }
        }
        return false;
    }

    bool is_check_mate(Color king_color,Board* board)  override{
        if(!is_in_check(king_color, board)) return false;

        vector<Position> pieces = board->get_all_pieces_of_color(king_color);
        for (const Position& pos : pieces){
            Piece* piece = board->get_piece(pos);
            vector<Position> moves = piece->get_possible_moves(pos, board);
            for (const Position& target_pos : moves){
                Move move = Move(pos, target_pos, piece, board->get_piece(target_pos));
                if (is_valid_move(move, board)) {
                    return false; // Found a valid move that gets out of check
                }
            }
        }
        return true;
    }
    bool is_stale_mate(Color king_color, Board* board)  override{
        if(is_in_check(king_color, board)) return false;

        vector<Position> pieces = board->get_all_pieces_of_color(king_color);
        for (const Position& pos : pieces){
            Piece* piece = board->get_piece(pos);
            vector<Position> moves = piece->get_possible_moves(pos, board);
            for (const Position& target_pos : moves){
                Move move = Move(pos, target_pos, piece, board->get_piece(target_pos));
                if (is_valid_move(move, board)) {
                    return false; // Found a valid move that gets out of check
                }
            }
        }
        return true;
    }
    bool would_move_cause_check(Move move, Board* board, Color king_color) override{
        Piece* moving_piece = board->get_piece(move.get_from());
        Piece* captured_piece = board->get_piece(move.get_to());
        
        if(!moving_piece) return true;
        
        board->remove_piece(move.get_from());
        if(captured_piece) board->remove_piece(move.get_to());
        board->place_piece(move.get_to(), moving_piece);

        bool in_check = is_in_check(king_color, board);

        board->remove_piece(move.get_to());
        board->place_piece(move.get_from(), moving_piece);
        if(captured_piece) board->place_piece(move.get_to(), captured_piece);

        return in_check;
    }
};