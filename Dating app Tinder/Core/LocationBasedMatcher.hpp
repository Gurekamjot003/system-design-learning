#pragma once
#include "InterestBasedMatcher.hpp"

class LocationBasedMatcher: public Matcher{
    InterestBasedMatcher* interest_matcher;
    
public:
    LocationBasedMatcher(): interest_matcher(new InterestBasedMatcher()){}

    double calculate_match_score(User* user1, User* user2) override{
        double interest_score = interest_matcher->calculate_match_score(user1, user2);
        if(interest_score == 0) return 0;

        Location* user1_location = user1->get_location(), *user2_location = user2->get_location();

        double distance = user1_location->distance_in_km(user2_location);
        if(!user1->check_location_preference(distance) or !user2->check_location_preference(distance)) return 0;

        double max_distance = min(user1->get_max_distance_preference(), user2->get_max_distance_preference());

        cout<<"\n[LocationBasedMatcher] Distance between "<<user1->get_user_id()<< " and "<<user2->get_user_id()<<": "<<distance<<endl;
        
        double score = (max_distance - distance)/max_distance;
        score = max(score, 0.2);


        double weightage = 0.2;

        double location_score = weightage * score;

        cout<<"[LocationBasedMatcher] Location Score: "<<location_score*100<<endl;

        return location_score + interest_score;
    }

    ~LocationBasedMatcher(){
        delete interest_matcher;
    }
};