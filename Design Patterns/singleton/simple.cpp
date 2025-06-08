#include<bits/stdc++.h>
using namespace std;

class Singleton{
private:
    static Singleton* instance;

    Singleton(){
        cout<<"Singleton constructor called"<<endl;
    }

public:
    static Singleton* get_instance(){
        if(!instance) instance = new Singleton();
        return instance;
    }
};

Singleton* Singleton::instance = NULL;

int main(){
    Singleton* s1 = Singleton::get_instance();
    Singleton* s2 = Singleton::get_instance();

    cout<<(s1 == s2)<<endl;
}