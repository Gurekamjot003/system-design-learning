#include<bits/stdc++.h>
using namespace std;

class IOffice{
protected:
    IOffice* higher_authority;

public:
    IOffice(){
        higher_authority = NULL;
    }

    void set_higher_authority(IOffice* higher_authority){
        this->higher_authority = higher_authority;
    }

    virtual void request_leave(int num_days) = 0;
};

class TeamLead: public IOffice{
private:
    int max_grantable_leave;

public: 
    TeamLead(int max_grantable_leave){
        this->max_grantable_leave = max_grantable_leave;
    }

    void request_leave(int num_days){
        if(num_days<=max_grantable_leave){
            cout<<"[TeamLead] The leave for "<<num_days<<" days has been granted."<<endl;
        }
        else if(higher_authority){
            higher_authority->request_leave(num_days);
        }
        else{
            cout<<"Leave denied."<<endl;
        }
    }

};

class Manager: public IOffice{
private:
    int max_grantable_leave;

public: 
    Manager(int max_grantable_leave){
        this->max_grantable_leave = max_grantable_leave;
    }

    void request_leave(int num_days){
        if(num_days<=max_grantable_leave){
            cout<<"[Manager] The leave for "<<num_days<<" days has been granted."<<endl;
        }
        else if(higher_authority){
            higher_authority->request_leave(num_days);
        }
        else{
            cout<<"Leave denied."<<endl;
        }
    }
};

class Director: public IOffice{
private:
    int max_grantable_leave;

public: 
    Director(int max_grantable_leave){
        this->max_grantable_leave = max_grantable_leave;
    }

    void request_leave(int num_days){
        if(num_days<=max_grantable_leave){
            cout<<"[Director] The leave for "<<num_days<<" days has been granted."<<endl;
        }
        else if(higher_authority){
            higher_authority->request_leave(num_days);
        }
        else{
            cout<<"Leave denied."<<endl;
        }
    }
};

class Employee{
private:
    IOffice* office;

public:
    Employee(IOffice* office){
        this->office = office;
    }

    void request_leave(int num_days){
        office->request_leave(num_days);
    }
};

int main(){
    IOffice* team_lead = new TeamLead(2);
    IOffice* manager = new Manager(5);
    IOffice* director = new Director(10);

    team_lead->set_higher_authority(manager);
    manager->set_higher_authority(director);

    Employee* gurekam = new Employee(team_lead);
    gurekam->request_leave(5);
}