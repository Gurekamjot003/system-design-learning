#pragma once
#include <bits/stdc++.h>
#include "../enums/PlayStrategyType.hpp"
#include "../strategies/sequentialPlayStrategy.hpp"
#include "../strategies/randomPlayStrategy.hpp"
#include "../strategies/customQueueStrategy.hpp"   
using namespace std;

class StrategyManager{
private:
    static StrategyManager* instance;
    SequentialPlayStrategy* sequential_strategy;
    RandomPlayStrategy* random_strategy;
    CustomQueueStrategy* custom_queue_strategy;

    StrategyManager() {
        sequential_strategy = new SequentialPlayStrategy();
        random_strategy = new RandomPlayStrategy();
        custom_queue_strategy = new CustomQueueStrategy();
    }

public:
    static StrategyManager* get_instance(){
        if(!instance){
            instance = new StrategyManager();
        }
        return instance;
    }

    PlayStrategy* get_strategy(PlayStrategyType type){
        switch(type){
            case PlayStrategyType::SEQUENTIAL:
                return sequential_strategy;
            case PlayStrategyType::RANDOM:
                return random_strategy;
            case PlayStrategyType::CUSTOM_QUEUE:
                return custom_queue_strategy;
            default:
                throw invalid_argument("Invalid PlayStrategyType");
        }
    }
};

StrategyManager* StrategyManager::instance = NULL;