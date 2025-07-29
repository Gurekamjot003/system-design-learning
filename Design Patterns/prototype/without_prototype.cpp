#include<bits/stdc++.h>
using namespace std;

class NPC{
public:
    string name;
    int health;
    int attack;
    int defense;

    NPC(string n, int h, int a, int d) : name(n), health(h), attack(a), defense(d) {
        cout<< "NPC created: " << name << " with Health: " << health 
            << ", Attack: " << attack << ", Defense: " << defense << endl;
    }  

    void display() {
        cout << "NPC Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defense: " << defense << endl;
    }
};

int main(){
    NPC npc1("Goblin", 100, 15, 5);
    npc1.display();
    NPC npc2("Orc", 150, 20, 10);
    npc2.display();
    return 0;
}