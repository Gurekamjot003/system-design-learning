//Dependency Inversion Principle

#include<bits/stdc++.h>
using namespace std;

// Abstraction (interface)

class Datbase{
public:
    virtual void save(string data) = 0;
};

class MySQLDatabase: public Datbase{    // low level module
public:
    void save(string data) override{
        cout<<"Executing SQL query: INSERT INTO users VALUES('"<<data<<"');"<<endl;
    }
};

class MongoDBDatabase: public Datbase{  // low level module
public:
    void save(string data) override{
        cout<<"Executing MongoDB function: db.users.insert({name: '"<<data<<"'})"<<endl;
    }
};

class UserService{  // High level module (now loosely coupled)
private:
    Datbase* db;

public:
    UserService(Datbase* database){
        db = database;
    }

    void store_user(string user){
        db->save(user);
    }
};

int main(){
    UserService* service1 = new UserService(new MySQLDatabase());
    UserService* service2 = new UserService(new MongoDBDatabase());
    service1->store_user("gurekam");
    service2->store_user("vt");
}