#pragma once
#include "NotificationObserver.hpp"

class UserNotificationObserver: public NotificationObserver{
    string user_id;
public:
    UserNotificationObserver(string user_id):user_id(user_id){}
    void update(string msg) override{
        cout<<"[UserNotificationService] User "<<user_id<<": "<<msg<<endl;
    }
};