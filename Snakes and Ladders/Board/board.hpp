#pragma once
#include "snake.hpp"
#include "ladder.hpp"
#include"player.hpp"
#include"dice.hpp"
#include "../Board setup/board_setup_strategy.hpp"

class Board{
    int size;
    vector<BoardEntity*> entities;
    unordered_map<int, BoardEntity*> entity_map;
public:
    Board(int size): size(size*size) {
        if (size <= 0) {
            throw invalid_argument("Board size must be greater than zero");
        }
    }

    bool can_add_entity(int position) {
        if(position<1 or position > size) return false;
        if (entity_map.find(position) != entity_map.end()) {
            return false;
        }
        return true;
    }

    void add_entity(BoardEntity* entity) {
        if (!can_add_entity(entity->start) or entity->start == entity->end or entity->end < 1 or entity->end > size) {
            throw invalid_argument("Entity cannot be added at the specified positions");
        }
        entities.push_back(entity);
        entity_map[entity->start] = entity;
    }

    void display() {
        cout << "Board Size: " << size << endl;
        cout << "Entities on the Board:" << endl;
        for (const auto& entity : entities) {
            entity->display();
        }
    }

    BoardEntity* get_entity_at(int position) {
        if (entity_map.find(position) != entity_map.end()) {
            return entity_map[position];
        }
        return nullptr; // No entity at this position
    }

    int get_size() const {
        return size;
    }

    vector<BoardEntity*> get_entities() const {
        return entities;
    }

    void setup(BoardSetupStrategy* strategy) {
        if (!strategy) {
            throw invalid_argument("Setup strategy cannot be null");
        }
        strategy->setup(this);
    }

    ~Board() {
        for (auto entity : entities) {
            delete entity; // Clean up dynamically allocated entities
        }
    }
};
