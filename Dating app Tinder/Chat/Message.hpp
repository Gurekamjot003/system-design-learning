#pragma once
#include<bits/stdc++.h>
using namespace std;

class Message{
    string sender_id, content;
    time_t time;

public:
    Message(string sender_id, string content):sender_id(sender_id), content(content){
        time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    }

    void display(){
        cout<<"Sender: "<<sender_id<<endl;
        cout<<"Content: "<<content<<endl;
        cout << "Time: " << ctime(&time);
    }
};