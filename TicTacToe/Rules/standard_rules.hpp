#pragma once
#include"irules.hpp"

class StandardRules : public IRules {
    public:
    bool is_valid_move(Board* board, int row, int col) override {
        return row >= 0 && row < board->get_size() && col >= 0 && col < board->get_size() && 
               board->is_cell_empty(row, col);
    }

    bool is_winner(Board* board, int row, int col) override{
        Symbol symbol = board->get_cell(row, col);
        int size = board->get_size();
        // Check row
        int i = col-1, j = col+1;
        while(i>=0 && board->get_cell(row, i).get_mark() == symbol.get_mark()) {
            i--;
        }
        while(j<size && board->get_cell(row, j).get_mark() == symbol.get_mark()) {
            j++;
        }
        if(j-i-1 >= 3) return true;
        // Check column
        i = row-1, j = row+1;
        while(i>=0 && board->get_cell(i, col).get_mark() == symbol.get_mark()) {
            i--;
        }   
        while(j<size && board->get_cell(j, col).get_mark() == symbol.get_mark()) {
            j++;
        }
        if(j-i-1 >= 3) return true;
        // Check diagonal 
        i = row-1, j = row+1;
        int k = col-1, l = col+1;
        while(i>=0 && k>=0 && board->get_cell(i, k).get_mark() == symbol.get_mark()) {
            i--; k--;
        }
        while(j<size && l<size && board->get_cell(j, l).get_mark() == symbol.get_mark()) {
            j++; l++;
        }
        if(j-i-1 >= 3) return true;
        // Check anti-diagonal
        i = row-1, j = row+1;
        k = col+1, l = col-1;
        while(i>=0 && k<size && board->get_cell(i, k).get_mark() == symbol.get_mark()) {
            i--; k++;
        }
        while(j<size && l>=0 && board->get_cell(j, l).get_mark() == symbol.get_mark()) {
            j++; l--;
        }
        return (j-i-1 >= 3);
    }

    bool is_draw(Board* board) override{
        return board->is_full();
    }
};