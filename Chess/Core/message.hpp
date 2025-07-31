#pragma once
#include<bits/stdc++.h>
using namespace std;

class Message{
private:
    string sender_id;
    string content;
    time_t time_stamp;

public:
    Message(string sender_id, string content) : sender_id(sender_id), content(content), time_stamp(time(nullptr)) {}

    string get_sender_id() const {
        return sender_id;
    }

    string get_content() const {
        return content;
    }

    time_t get_time_stamp() const {
        return time_stamp;
    }

    string to_string(){
        return "["+sender_id + "]: " + content;
    }
};