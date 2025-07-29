#include<bits/stdc++.h>
using namespace std;

class IColleague;

class IMediator{
public:
    virtual void send_message_to_all(string from, string message) = 0;
    virtual void send_private_message(string from, string to, string message) = 0;
    virtual void register_colleague(IColleague* colleague, string name) = 0;
    virtual void mute_user(string user_name, string muted_user_name) = 0;
};

class IColleague {
protected:
    IMediator* mediator;

public:
    IColleague(IMediator* mediator, string name) : mediator(mediator) {
        mediator->register_colleague(this, name);
    }

    virtual void send_message_to_all(string message) = 0;
    virtual void send_private_message(string to, string message) = 0;
    virtual void receive_message(string from, string message) = 0;
    virtual string get_name() = 0;
};

class User: public IColleague {
private:
    string name;

public:
    User(string name, IMediator* mediator) : IColleague(mediator, name), name(name) {}    

    string get_name() override {
        return name;
    }

    void send_message_to_all(string message) override {
        mediator->send_message_to_all(name, message);
    }

    void send_private_message(string to, string message) override {
        mediator->send_private_message(name, to, message);
    }

    void receive_message(string from, string message) override {
        cout << name << " received message from " << from << ": " << message << endl;
    }
};
class ChatMediator: public IMediator {
private:
    unordered_map<string, IColleague*> colleagues;
    unordered_map<string, unordered_set<string>> muted_users;

public: 
    void register_colleague(IColleague* colleague, string name) override {
        colleagues[name] = colleague;
    }

    void mute_user(string user_name, string muted_user_name) {
        muted_users[user_name].insert(muted_user_name);
    }

    void send_message_to_all(string from, string message) override {
        for (auto& [name, colleague] : colleagues) {
            if (name != from && !muted_users[name].count(from)) {
                colleague->receive_message(from, message);
            } else if (name != from) {
                cout << from << " tried to send message to " << name << ", but they are muted." << endl;
            }
        }
    }

    void send_private_message(string from, string to, string message) override {
        if (colleagues.count(to)) {
            if (!muted_users[to].count(from)) {
                colleagues[to]->receive_message(from, message);
            } else {
                cout << from << " tried to send a message to " << to << ", but they are muted." << endl;
            }
        } else {
            cout << "User " << to << " not found." << endl;
        }
    }
};

int main(){
    IMediator* chatroom = new ChatMediator();
    IColleague* gurekam = new User("Gurekam", chatroom);
    IColleague* vt = new User("VT", chatroom);
    IColleague* ekroop = new User("Ekroop", chatroom);

    chatroom->mute_user("Ekroop", "VT");

    gurekam->send_message_to_all("Hello everyone!");
    vt->send_message_to_all("Hi all!");

    gurekam->send_private_message("VT", "hello vai!");

    delete gurekam;
    delete vt;
    delete ekroop;
    delete chatroom;
}
