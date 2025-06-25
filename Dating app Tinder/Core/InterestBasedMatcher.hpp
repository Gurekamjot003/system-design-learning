#pragma once
#include "BasicMatcher.hpp"

class InterestBasedMatcher: public Matcher{
    BasicMatcher* basic_matcher;
    
public:
    InterestBasedMatcher(): basic_matcher(new BasicMatcher()){}
    
    double calculate_match_score(User* user1, User* user2) override{
        double basic_score = basic_matcher->calculate_match_score(user1, user2);
        if(basic_score == 0) return 0;
        
        vector<Interest*> user1_interests = user1->get_interests(), user2_interests = user2->get_interests();
        
        cout<<"\n[InterestBasedMatcher] Matching preference interests: "<<endl;
        
        vector<Interest*> user2_interest_preference_matched = get_matched_interests(user1, user2);
        int interest_match_count2 = user2_interest_preference_matched.size();

        vector<Interest*> user1_interest_preference_matched = get_matched_interests(user2, user1);
        int interest_match_count1 = user1_interest_preference_matched.size();
        
        cout<<user1->get_user_id() <<": "<<endl;
        for(auto& interest: user1_interest_preference_matched) cout<<interest->get_interest()<<endl;
        cout<<user2->get_user_id() <<": "<<endl;
        for(auto& interest: user2_interest_preference_matched) cout<<interest->get_interest()<<endl;

        int interest_match = min(interest_match_count1, interest_match_count2);
        cout<<"[InterestBasedMatcher] No of matching interests: "<<interest_match<<endl;
        
        double val = 0.5;
        double score = 0;
        while(interest_match--){
            score += val;
            val *= 0.5;
        }

        double weightage = 0.5;
        double interest_score = score * weightage;
        cout<<"[InterestBasedMatcher] Interest Score: "<<interest_score*100<<endl;
        
        return interest_score + basic_score;
    }

    ~InterestBasedMatcher(){
        delete basic_matcher;
    }

    vector<Interest*> get_matched_interests(User* user1, User* user2){
        vector<Interest*> interest_preference_match_for_user2;

        for(auto& u1_interest: user1->get_interests()){
            if(user2->check_interest_preference(u1_interest)){
                interest_preference_match_for_user2.push_back(u1_interest);
            }
        }
        return interest_preference_match_for_user2;
    }
};