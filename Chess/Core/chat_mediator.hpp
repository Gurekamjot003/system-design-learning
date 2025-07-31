#pragma once
#include "message.hpp"
#include "../Rules/standard_rules.hpp"

class ChatMediator{
    
public:
    virtual void send_message(Message message) = 0;
    virtual void add_user(User* user) = 0;
    virtual void remove_user(User* user) = 0;
};