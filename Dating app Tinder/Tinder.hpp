#pragma once
#include "Location/LocationService.hpp"
#include "Core/MatcherFactory.hpp"
#include "Chat/Chatroom.hpp"

class Tinder{
    vector<User*> users;
    vector<Chatroom*> chatrooms;
    Matcher* matcher;
    static Tinder* instance;
    Tinder(){}
    
public:
    static Tinder* get_instance(){
        if(!instance) instance = new Tinder();
        return instance;
    }

    ~Tinder(){
        for(auto& user: users) delete user;
        for(auto& chatroom: chatrooms) delete chatroom;
        delete matcher;
    }

    void initialize(){
        UserProfile* gurekam_profile = new UserProfile("Gurekam", 21, Gender::MALE, new Location(31.6340, 74.8723) /*amritsar*/);
        gurekam_profile->add_photo("photo1.jpg");
        gurekam_profile->add_interest(new Interest("Coding", "Tech"));
        gurekam_profile->add_interest(new Interest("Singing", "Music"));
        gurekam_profile->add_interest(new Interest("Chess", "Strategy"));

        gurekam_profile->set_bio("Engineer by day, code whisperer by night. I enjoy deep conversations, mountains, and building cool things that make life better.");
        
        Preference* p1 = new Preference(18, 22, 100);
        for(auto& interest: gurekam_profile->get_interests()){
            p1->add_interest(interest->get_name());
        }
        p1->add_interest("Cooking");
        p1->add_interest("Music");
        p1->add_gender_interest(Gender::FEMALE);

        User* Gurekam = create_user("gurekam", gurekam_profile);
        Gurekam->set_preference(p1);

        UserProfile* user2_profile = new UserProfile("user2", 20, Gender::FEMALE, new Location(31.3260, 75.5762) /*any city withing 100 km eg jalandhar*/);
        user2_profile->add_photo("photo2.jpg");
        user2_profile->add_interest(new Interest("Coding", "Tech"));
        user2_profile->add_interest(new Interest("Religious", "Sprituality"));
        user2_profile->add_interest(new Interest("Music", "Music"));

        user2_profile->set_bio("Spiritual soul with a love for clean code. I believe bugs in life (and programs) are meant to be fixed.");

        Preference* p2 = new Preference(19, 23, 150);
        for(auto& interest: user2_profile->get_interests()){
            p2->add_interest(interest->get_name());
        }
        p2->add_gender_interest(Gender::MALE);

        
        User* user2 = create_user("user2", user2_profile);
        user2->set_preference(p2);

    }

    void set_matcher(MatcherType matcher_type){
        matcher = MatcherFactory::get_instance()->create_matcher(matcher_type);
    }

    User* create_user(string user_id, UserProfile* profile){
        for(auto& user: users){
            if(user->get_user_id() == user_id){
                cout<<"[Tinder] Error: User already exists"<<endl;
                return NULL;
            }
        }
        cout<<"[Tinder] Created new user with user_id "<<user_id<<endl;
        User* user = new User(user_id, profile);
        users.push_back(user);
        return user;
    }

    void display_nearby_users(string user_id){
        cout<<"[Tinder] Displaying nearby users for "<<user_id<<endl;
        vector<User*> users = get_nearby_users(user_id);
        for(auto& user: users){
            cout<<user->get_user_id()<<endl;
        }
    }

    vector<User*> get_nearby_users(string user_id){
        User* user = get_user_by_id(user_id);
        double max_distance = user->get_max_distance_preference();
        return LocationService::get_instance()->find_nearby_users(user->get_location(), max_distance, users, user);
    }

    User* get_user_by_id(string user_id){
        for(auto& user: users){
            if(user->get_user_id() == user_id) return user;
        }
        return NULL;
    }

    void swipe(string user_id, string target_id, SwipeAction action){
        User* user = get_user_by_id(user_id);
        User* other_user = get_user_by_id(target_id);
        user->swipe(target_id, action);

        if(other_user->has_liked(user_id) && action == SwipeAction::RIGHT){ //match condition
            vector<string> participants;
            participants.push_back(user_id);
            participants.push_back(target_id);
            Chatroom* chatroom = new Chatroom(participants);
            chatrooms.push_back(chatroom);
            
            double score = matcher->calculate_match_score(user, other_user);
            cout<<fixed<<setprecision(1)<<"\nMatchScore = "<<score*100<<"\n\n";
            NotificationService::get_instance()->notify(user_id, "You matched with " + other_user->get_user_id() + "!");
            NotificationService::get_instance()->notify(other_user->get_user_id(), "You matched with " + user_id + "!");


        }
    }

    Chatroom* get_chatroom_by_ids(string user1, string user2){
        vector<string> participants;
        participants.push_back(user1);
        participants.push_back(user2);
        sort(participants.begin(), participants.end());
        string target_id;
        for(auto& user_id: participants){
            target_id += user_id + "_";
        }

        for(auto& chatroom: chatrooms){
            if(chatroom->get_id() == target_id) return chatroom;
        }
        return NULL;
    }

    void send_message(string sender, string reciever, string content){
        Chatroom* chatroom = get_chatroom_by_ids(sender, reciever);
        if(!chatroom){
            cout<<"[Tinder] User "<<sender<<" and user "<<reciever<<" have not matched. Message not sent"<<endl;
            return;
        }
        chatroom->add_message(sender, content);
    }

    void display_chat(string user1, string user2){
        Chatroom* chatroom = get_chatroom_by_ids(user1, user2);
        if(!chatroom){
            cout<<"No chatroom found"<<endl;
            return;
        }
        chatroom->display_chat();
    }
};

Tinder* Tinder::instance = NULL;