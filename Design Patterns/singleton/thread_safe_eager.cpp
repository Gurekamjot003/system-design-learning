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
        return instance;
    }
};

Singleton* Singleton::instance = new Singleton();

int main(){
    Singleton* s1 = Singleton::get_instance();
    Singleton* s2 = Singleton::get_instance();

    cout<<(s1 == s2)<<endl;
}