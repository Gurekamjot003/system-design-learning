#pragma once
#include"SplitType.hpp"
#include"ExactSplit.hpp"
#include"EqualSplit.hpp"
#include"PercentSplit.hpp"

class SplitFactory{
public:
    static SplitStrategy* get_split_strategy(SplitType type){
        if(type == SplitType::EQUAL) return new EqualSplit();
        if(type == SplitType::EXACT) return new ExactSplit();
        if(type == SplitType::PERCENTAGE) return new PercentSplit();
        return new EqualSplit(); // default
    }
};