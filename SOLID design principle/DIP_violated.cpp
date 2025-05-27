//Dependency Inversion Principle

#include<bits/stdc++.h>
using namespace std;

class MySQLDatabase{    // low level module
public:
    void save_to_SQL(string data){
        cout<<"Executing SQL query: INSERT INTO users VALUES('"<<data<<"');"<<endl;
    }
};

class MongoDBDatabase{  // low level module
public:
    void save_to_Mongo(string data){
        cout<<"Executing MongoDB function: db.users.insert({name: '"<<data<<"'})"<<endl;
    }
};

class UserService{  // High level module
private:
    MySQLDatabase sqlDB;
    MongoDBDatabase mongoDB;

public:
    void store_user_to_SQL(string user){
        sqlDB.save_to_SQL(user);
    }
    void store_user_to_mongo(string user){
        mongoDB.save_to_Mongo(user);
    }
};

int main(){
    UserService service;
    service.store_user_to_mongo("gurekam");
    service.store_user_to_SQL("vt");
}