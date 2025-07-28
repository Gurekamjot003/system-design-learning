#pragma once
#include"../Player/symbol.hpp"

#define vvs vector<vector<Symbol>>

class Board{
    vvs grid;
    int size;
    Symbol empty_symbol;
    int filled = 0;
public:
    Board(int size, Symbol empty_symbol) : size(size), empty_symbol(empty_symbol) {
        grid.resize(size, vector<Symbol>(size, empty_symbol));
    }

    int get_size() const {
        return size;
    }

    Symbol get_empty_symbol() const {
        return empty_symbol;
    }

    Symbol get_cell(int row, int col) const {
        return grid[row][col];
    }

    void set_cell(int row, int col, Symbol symbol) {
        grid[row][col] = symbol;
    }

    bool is_full() {
        return filled == size * size;
    }

    void place_mark(int row, int col, Symbol symbol){
        grid[row][col] = symbol;
        filled++;
    }

    bool is_cell_empty(int row, int col) {
        return grid[row][col].get_mark() == empty_symbol.get_mark();
    }

    void display(){
        cout<<"\n\nBoard: "<<endl;
        cout<<"  ";
        for(int i = 0; i<size; i++){
            cout<<i<<" ";
        }
        cout<<endl;
        int j = 0;
        for(auto& row: grid){
            cout<<j++<<" ";
            for(auto& cell: row){
                cout<<cell.get_mark()<<" ";
            }
            cout<<endl;
        }
    }
};