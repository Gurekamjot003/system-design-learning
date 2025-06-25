#pragma once 
#include "UserNotificationObserver.hpp"

class NotificationService{
    map<string, NotificationObserver*> observers;
    static NotificationService* instance;
    NotificationService(){}

public:
    static NotificationService* get_instance(){
        if(!instance) instance = new NotificationService();
        return instance;
    }

    void add(string user_id, NotificationObserver* observer){
        observers[user_id] = observer;
    }

    void remove(string user_id){
        observers.erase(user_id);
    }

    void notify(string user_id, string msg){
        if(observers.find(user_id) == observers.end()) return;
        NotificationObserver* observer = observers[user_id];
        observer->update(msg);
    }

    void notify_all(string msg){
        for(auto&[user_id, observer]: observers){
            observer->update(msg);
        }
    }

    
};

NotificationService* NotificationService::instance = NULL;