#pragma once
#include "Preference.hpp"
#include"UserProfile.hpp"
#include "../Notification/NotificationService.hpp"
#include "SwipeAction.hpp"

class User{
    string user_id;
    UserProfile* user_profile;
    Preference* preference;
    map<string, SwipeAction> swipe_history;
    NotificationObserver* notification_observer;

public:
    User(string user_id, UserProfile* user_profile):user_id(user_id), user_profile(user_profile), notification_observer(new UserNotificationObserver(user_id)) {
        NotificationService::get_instance()->add(user_id, notification_observer);
        preference = NULL;
    }

    void set_preference(Preference* preference){
        if(this->preference) 
            delete this->preference;        
        this->preference = preference;
    }
    
    ~User(){
        delete user_profile;
        delete preference;
        NotificationService::get_instance()->remove(user_id);
        delete notification_observer;
    }

    void swipe(string other_user_id, SwipeAction action){
        swipe_history[other_user_id] = action;
    }

    bool has_liked(string user_id){
        if(swipe_history.find(user_id) != swipe_history.end()){
            if(swipe_history[user_id] == SwipeAction::RIGHT) return true;
        }
        return false;
    }

    bool has_disliked(string user_id){
        if(swipe_history.find(user_id) == swipe_history.end()) return true;
        if(swipe_history[user_id] == SwipeAction::LEFT) return true;
        return false;
    }

    bool has_interacted_with(string user_id){
        return swipe_history.find(user_id) != swipe_history.end();
    }

    Location* get_location(){
        return user_profile->get_location();
    }

    int get_age(){
        return user_profile->get_age();
    }

    bool check_age_preference(int age){
        return preference->check_age(age);
    }

    string get_user_id(){
        return user_id;
    }

    Gender get_gender(){
        return user_profile->get_gender();
    }

    bool check_gender_preference(Gender gender){
        return preference->check_interested_in(gender);
    }

    bool check_interest_preference(Interest* interest){
        return preference->check_interest(interest);
    }

    vector<Interest*> get_interests(){
        return user_profile->get_interests();
    }

    bool check_location_preference(double distance){
        return preference->check_distance(distance);
    }

    double get_max_distance_preference(){
        return preference->get_max_distance();
    }

    void add_photo(string path){
        user_profile->add_photo(path);
    }

    void display_profile(){
        user_profile->display();
    }
};