#pragma once
#include"Matcher.hpp"

class BasicMatcher: public Matcher{
public:
    double calculate_match_score(User* user1, User* user2) override{
        if(!user1->has_interacted_with(user2->get_user_id()) or !user2->has_interacted_with(user1->get_user_id())) return 0;

        if(user1->has_disliked(user2->get_user_id()) or user2->has_disliked(user1->get_user_id())) return 0;

        int user1_age = user1->get_age();
        if(!user2->check_age_preference(user1_age)) return 0;

        int user2_age = user2->get_age();
        if(!user1->check_age_preference(user2_age)) return 0;

        Gender user1_gender = user1->get_gender();
        if(!user2->check_gender_preference(user1_gender)) return 0;

        Gender user2_gender = user2->get_gender();
        if(!user1->check_gender_preference(user2_gender)) return 0;

        cout<<"\n[BasicMatcher] "<<user1->get_user_id()<<" and "<< user2->get_user_id() << " Have liked each other and their gender and age preferences have been matched." <<endl;
        cout<<"[BasicMatcher] Score = 33"<<endl;
        return 0.33;
    }
};