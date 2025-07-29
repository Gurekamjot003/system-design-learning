#include<bits/stdc++.h>
using namespace std;

class User{
private:
    string name;
    unordered_map<string, User*> peers;
    unordered_set<string> muted_users;

public:
    User(string name) : name(name) {}

    string get_name(){
        return name;
    }

    void add_peer(User* user){
        peers[user->get_name()] = user;
    }

    User* get_peer_from_name(string name){
        if(peers.count(name)) return peers[name];
        return nullptr;
    }

    void mute(string user_to_mute){
        muted_users.insert(user_to_mute);
    }

    bool is_muted(string user_name){
        return muted_users.count(user_name);
    }

    void send_message_to_all(string message){
        for(auto& peer : peers){
            if(!peer.second->is_muted(name)){
                peer.second->recieve_message(name, message);
            } else {
                cout << name << " tried to send message to " << peer.first << ", but they are muted." << endl;
            }
        }
    }

    void send_message_to(string from_user_name, string to_user_name, string message){
        User* to_user = get_peer_from_name(to_user_name);
        if(to_user){
            if(to_user->is_muted(from_user_name)){
                cout << from_user_name << " tried to send a message to " << to_user_name << ", but they are muted." << endl;
                return;
            }
            to_user->recieve_message(from_user_name, message);
        } else {
            cout << "User " << to_user_name << " not found." << endl;
        }
    }

    void recieve_message(string from_user_name, string message){
        cout<< name << " received message from " << from_user_name << ": " << message << endl;
    }
};

int main(){

    User* gurekam = new User("Gurekam");
    User* vt = new User("VT");
    User* ekroop = new User("Ekroop");

    gurekam->add_peer(vt);
    vt->add_peer(gurekam);

    vt->add_peer(ekroop);
    ekroop->add_peer(vt);

    ekroop->add_peer(gurekam);
    gurekam->add_peer(ekroop);

    ekroop->mute("VT");

    gurekam->send_message_to_all("Hello everyone!");
    vt->send_message_to_all("Hello everyone!");

    gurekam->send_message_to("Gurekam", "VT", "Hello vai!");

    delete gurekam;
    delete vt;
    delete ekroop;
}