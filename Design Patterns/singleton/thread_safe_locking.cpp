#include <iostream>
#include <mutex>
using namespace std;

class Singleton{
private:
    static Singleton* instance;
    static std::mutex mtx;

    Singleton(){
        cout<<"Singleton constructor called"<<endl;
    }

public:
    static Singleton* get_instance(){
        if(!instance){
            lock_guard<mutex> lock(mtx);
            if(!instance){
                instance = new Singleton();
            }
        }
        return instance;
    }
};

Singleton* Singleton::instance = NULL;
std::mutex Singleton::mtx;

int main(){
    Singleton* s1 = Singleton::get_instance();
    Singleton* s2 = Singleton::get_instance();

    cout<<(s1 == s2)<<endl;
}