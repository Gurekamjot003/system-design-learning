#pragma once
#include "LocationBasedMatcher.hpp"
#include "MatcherType.hpp"

class MatcherFactory{
    static MatcherFactory* instance;
    MatcherFactory(){}

public:
    static MatcherFactory* get_instance(){
        if(!instance) instance = new MatcherFactory();
        return instance;
    }

    Matcher* create_matcher(MatcherType matcher_type){
        if(matcher_type == MatcherType::BASIC) return new BasicMatcher();
        if(matcher_type == MatcherType::INTEREST) return new InterestBasedMatcher();
        if(matcher_type == MatcherType::LOCATION) return new LocationBasedMatcher();
        return NULL;
    }
};

MatcherFactory* MatcherFactory::instance = NULL;