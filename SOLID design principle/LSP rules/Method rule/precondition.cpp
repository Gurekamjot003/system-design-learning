// a precondition must be satisfied before a method can be executed. sub classes can weaken the precondition but cannot strengthen it.

#include<bits/stdc++.h>
using namespace std;

class User{
public:
    virtual void set_password(string password){
        if(password.length()<8){
            throw invalid_argument("Password must be at least 8 characters long");
        }
        cout<<"Password set successfully!"<<endl;
    }
};

class AdminUser: public User{
public:
    void set_password(string password) override{
        if(password.length()<6){
            throw invalid_argument("Password must be at least 6 characters long");
        }
        cout<<"Password set successfully!"<<endl;
    }
};

int main(){
    User* user = new AdminUser();
    user->set_password("abcdefgh");
    user->set_password("abcdef");
}