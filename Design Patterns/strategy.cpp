#include<bits/stdc++.h>
using namespace std;

class WalkableRobot{
public:
    virtual void walk() = 0;
    virtual ~WalkableRobot(){}
};

class NormalWalk: public WalkableRobot{
public:   
    void walk() override{
        cout<<"Walking normally..."<<endl;
    }
};

class NoWalk: public WalkableRobot{
public:
    void walk() override{
        cout<<"Cannot walk."<<endl;
    }
};

class TalkableRobot{
public:
    virtual void talk() = 0;
    virtual ~TalkableRobot(){}
};

class NormalTalk: public TalkableRobot{
public:   
    void talk() override{
        cout<<"Talking normally..."<<endl;
    }
};

class NoTalk: public TalkableRobot{
public:
    void talk() override{
        cout<<"Cannot talk."<<endl;
    }
};

class FlyableRobot{
public:
    virtual void fly() = 0;
    virtual ~FlyableRobot(){}
};

class NormalFly: public FlyableRobot{
public:   
    void fly() override{
        cout<<"flying normally..."<<endl;
    }
};

class NoFly: public FlyableRobot{
public:
    void fly() override{
        cout<<"Cannot fly."<<endl;
    }
};

class Robot{
protected:
    WalkableRobot* walk_behavior;
    TalkableRobot* talk_behavior;
    FlyableRobot* fly_behavior;

public:
    Robot(WalkableRobot* walk_behavior, TalkableRobot* talk_behavior, FlyableRobot* fly_behavior){
        this->walk_behavior = walk_behavior;
        this->talk_behavior = talk_behavior;
        this->fly_behavior = fly_behavior;
    }  

    void walk(){
        walk_behavior->walk();
    }

    void talk(){
        talk_behavior->talk();
    }

    void fly(){
        fly_behavior->fly();
    }

    virtual void projection() = 0;
};

class CompanionRobot: public Robot{
public:
    CompanionRobot(WalkableRobot* walk_behavior, TalkableRobot* talk_behavior, FlyableRobot* fly_behavior):Robot(walk_behavior, talk_behavior, fly_behavior){}

    void projection() override{
        cout<<"Displaying friendly companion features..."<<endl;
    }
};

class WorkerRobot: public Robot{
public:
    WorkerRobot(WalkableRobot* walk_behavior, TalkableRobot* talk_behavior, FlyableRobot* fly_behavior):Robot(walk_behavior, talk_behavior, fly_behavior){}

    void projection() override{
        cout<<"Displaying worker efficiency stats..."<<endl;
    }
};

int main(){
    Robot* robot1 = new CompanionRobot(new NormalWalk(), new NormalTalk(), new NoFly());
    robot1->walk();
    robot1->talk();
    robot1->fly();
    robot1->projection();
    
    cout<<"---------------------------"<<endl;
    
    Robot* robot2 = new WorkerRobot(new NoWalk(), new NoTalk(), new NormalFly());
    robot2->walk();
    robot2->talk();
    robot2->fly();
    robot2->projection();

}