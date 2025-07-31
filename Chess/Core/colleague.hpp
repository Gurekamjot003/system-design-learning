#pragma once
#include "chat_mediator.hpp"

class Colleague{
    
protected:
    ChatMediator* mediator;

public:
    Colleague(ChatMediator* mediator) : mediator(mediator) {}
    
    virtual void receive_message(Message* message) = 0;
    virtual void send_message(Message* message) = 0;
    virtual void set_mediator(ChatMediator* mediator){
        this->mediator = mediator;
    }

    ChatMediator* get_mediator(){
        return mediator;
    }
};