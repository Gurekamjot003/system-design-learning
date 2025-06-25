#pragma once
#include"Message.hpp"
#include "../Notification/NotificationService.hpp"

class Chatroom{
    string id;
    vector<string> participants;
    vector<Message*> messages;

public:
    Chatroom(vector<string> participants) : participants(participants){
        sort(participants.begin(), participants.end());
        string id;
        for(auto& pid: participants) id += pid + "_";
        this->id = id;
    }

    void add_message(string sender_id, string content){
        if(find(participants.begin(), participants.end(), sender_id) == participants.end()) return;
        Message* message = new Message(sender_id, content);
        for(auto& user_id: participants){
            if(user_id != sender_id){
                NotificationService::get_instance()->notify(user_id, "You have recieved a message.");
            }
        }
        messages.push_back(message);
    }

    void display_chat(){
        cout<<"\n\nChatroom "<<id<<endl;
        for(auto& msg: messages){
            msg->display();
            cout<<endl;
        }
    }

    string get_id(){
        return id;
    }
};