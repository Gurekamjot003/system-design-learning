#include<bits/stdc++.h>
using namespace std;

class ISubscriber{
public:
    virtual void update() = 0;
    virtual ~ISubscriber(){}
};

class IChannel{
public:
    virtual void subscribe(ISubscriber* subscriber) = 0;
    virtual void unsubscribe(ISubscriber* subsriber) = 0;
    virtual void notify_subscribers() = 0;
    virtual ~IChannel(){}
};

class Channel: public IChannel{
private:
    vector<ISubscriber*> subscribers;
    string name;
    string latest_video;

public:
    Channel(string name){
        this->name = name;
    }

    void subscribe(ISubscriber* subscriber) override{
        if(find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()){
            subscribers.push_back(subscriber);
        }
    }
    
    void unsubscribe(ISubscriber* subscriber) override{
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);
        if(it != subscribers.end()){
            subscribers.erase(it);
        }
    }

    void notify_subscribers() override{
        for(auto sub: subscribers){
            sub->update();
        }
    }

    void upload_video(string title){
        latest_video = title;
        cout<<"\n["<<name<<" uploaded \""<<title<<"\"]"<<endl;
        notify_subscribers();
    }

    string get_video_data(){
        return "\nCheckout our new video: " + latest_video + "\n";
    }
};

class Subscriber: public ISubscriber{
private: 
    string name;
    Channel* channel;

public:
    Subscriber(string name, Channel* channel){
        this->name = name;
        this->channel = channel;
    }

    void update() override{
        cout<<"Hey "<<name<<", "<<this->channel->get_video_data();
    }
};

int main(){
    Channel* channel = new Channel("Coder army");

    Subscriber* sub1 = new Subscriber("Gurekamjot", channel);
    Subscriber* sub2 = new Subscriber("Vansh", channel);

    channel->subscribe(sub1);
    channel->subscribe(sub2);

    channel->upload_video("DSA in c++");

    channel->unsubscribe(sub2);

    channel->upload_video("System Design");

}