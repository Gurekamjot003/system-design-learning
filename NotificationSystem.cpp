#include<bits/stdc++.h>
using namespace std;

class INotification{
public:
    virtual string get_content() = 0;
    virtual ~INotification(){}
};

class SimpleNotification: public INotification{
private:
    string text;

public:
    SimpleNotification(string msg){
        this->text = msg;
    }

    string get_content(){
        return text;
    }
};

class INotificationDecorator: public INotification{
protected:
    INotification* notification;

public:
    INotificationDecorator(INotification* notification){
        this->notification = notification;
    }

    virtual ~INotificationDecorator() {
        delete notification;
    }
};

class TimeStampDecorator: public INotificationDecorator{
public:
    TimeStampDecorator(INotification* notification) : INotificationDecorator(notification){}

    string get_content() override{
        return "[2025-06-10 20:45:40]" + notification->get_content();
    }
};

class SignatureDecorator: public INotificationDecorator{
private:
    string signature;
public:
    SignatureDecorator(INotification* notification, string signature) : INotificationDecorator(notification){
        this->signature = signature;
    }

    string get_content() override{
        return notification->get_content() + "\n-- " + signature + "\n\n";
    }
};

class IObserver{
public:
    virtual void update() = 0;
    virtual ~IObserver() {}
};

class IObservalble{
public:
    virtual void add_observer(IObserver* observer) = 0;
    virtual void remove_observer(IObserver* observer) = 0;
    virtual void notify_observers() = 0;
};

class NotificationObservable: public IObservalble{
private:
    vector<IObserver*> observers;
    INotification* current_notification;

public:
    NotificationObservable(){
        current_notification =  NULL;
    }

    void add_observer(IObserver* observer) override{
        observers.push_back(observer);
    }

    void remove_observer(IObserver* observer) override{
        auto it = find(observers.begin(), observers.end(), observer);
        observers.erase(it);
    }

    void set_notification(INotification* notification){
        if(current_notification){
            delete current_notification;
        }
        current_notification = notification;
        notify_observers();
    }

    INotification* get_notification(){
        return current_notification;
    }

    void notify_observers() override{
        for(auto& observer: observers){
            observer->update();
        }
    }

    string get_notification_content(){
        return current_notification->get_content();
    }

    ~NotificationObservable(){
        delete current_notification;
    }
};

class Logger: public IObserver{
private:
    NotificationObservable* notification_observable;

public:
    Logger(NotificationObservable* no){
        notification_observable = no;
    }

    void update(){
        cout<<"Logging new Notification: \n"<<notification_observable->get_notification_content()<<endl;
    }
};

class INotificationStrategy{
public:
    virtual void send_notification(string content) = 0;
};

class EmailStrategy: public INotificationStrategy{
private:
    string email_id;

public:
    EmailStrategy(string email){
        email_id = email;
    }

    void send_notification(string content) override{
        cout<<"Sending email Notification to: "<<email_id<<endl<<content<<endl;
    }
};

class SMSStrategy: public INotificationStrategy{
private:
    string phone_number;

public:
    SMSStrategy(string phone_number){
        this->phone_number = phone_number;
    }

    void send_notification(string content) override{
        cout<<"Sending SMS Notification to: "<<phone_number<<endl<<content<<endl;
    }
};

class PopUpStrategy: public INotificationStrategy{
public:
    void send_notification(string content) override{
        cout<<"Sending Pop up Notification:" <<endl<<content<<endl;
    }
};

class NotificationEngine: public IObserver{
private:
    NotificationObservable* notification_observable;
    vector<INotificationStrategy*> notification_strategies;

public:
    NotificationEngine(NotificationObservable* observable){
        this->notification_observable = observable;
    }

    void add_notification_strategy(INotificationStrategy* no){
        notification_strategies.push_back(no);
    }

    void update(){
        string notification_content = notification_observable->get_notification_content();
        for(auto& notification: notification_strategies){
            notification->send_notification(notification_content);
        }
    }
};

class NotificationService{
private:
    vector<INotification*> notifications;
    NotificationObservable* observable;
    static NotificationService* instance;

    NotificationService(){
        observable = new NotificationObservable();
    }

public:
    static NotificationService* get_instance(){
        if(!instance){
            instance = new NotificationService();
        }
        return instance;
    }

    NotificationObservable* get_observable(){
        return observable;
    }

    void sent_notification(INotification* notification){
        notifications.push_back(notification);
        observable->set_notification(notification);
    }

    ~NotificationService(){
        delete observable;
    }
};

NotificationService* NotificationService::instance = NULL;

int main(){
    NotificationService* notification_service = NotificationService::get_instance();

    NotificationObservable* notification_observable = notification_service->get_observable();

    Logger* logger = new Logger(notification_observable);

    NotificationEngine* notification_engine = new NotificationEngine(notification_observable);

    notification_engine->add_notification_strategy(new EmailStrategy("abc@gmail.com"));
    notification_engine->add_notification_strategy(new SMSStrategy("1234567890"));
    notification_engine->add_notification_strategy(new PopUpStrategy());

    notification_observable->add_observer(logger);
    notification_observable->add_observer(notification_engine);

    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimeStampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer care");

    notification_service->sent_notification(notification);

    delete logger;
    delete notification_engine;
}