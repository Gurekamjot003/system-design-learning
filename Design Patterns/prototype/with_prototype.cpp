#include<bits/stdc++.h>
using namespace std;

class Cloneable{
public:
    virtual Cloneable* clone() const = 0; // Pure virtual function for cloning
    virtual ~Cloneable() {} // Virtual destructor
};

class NPC : public Cloneable {
public:
    string name;
    int health;
    int attack;
    int defense;

    NPC(string n, int h, int a, int d) : name(n), health(h), attack(a), defense(d) {
        cout << "NPC created: " << name << " with Health: " << health 
             << ", Attack: " << attack << ", Defense: " << defense << endl;
    }

    NPC(const NPC& other) : name(other.name), health(other.health), 
        attack(other.attack), defense(other.defense) {
        cout << "NPC copied: " << name << endl;
    }

    Cloneable* clone() const override {
        return new NPC(*this); // Create a new NPC by copying
    }

    void display() {
        cout << "NPC Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defense: " << defense << endl;
    }

    void set_name(const string& n) {
        name = n;
    }

    void set_health(int h) {
        health = h;
    }

    void set_attack(int a) {
        attack = a;
    }

    void set_defense(int d) {
        defense = d;
    }
};


int main(){
    NPC npc1("Goblin", 100, 15, 5);
    npc1.display();

    // Cloning npc1
    Cloneable* npcClone = npc1.clone();
    NPC* clonedNPC = dynamic_cast<NPC*>(npcClone);
    if (clonedNPC) {
        clonedNPC->display();
    }

    // Modifying the cloned NPC
    clonedNPC->set_name("Cloned Goblin");
    clonedNPC->set_health(120);
    clonedNPC->set_attack(18);
    clonedNPC->set_defense(7);
    clonedNPC->display();

    delete npcClone; // Clean up cloned object
    return 0;
}
