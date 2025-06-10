#include<bits/stdc++.h>
using namespace std;

class ICharacter{
public:
    virtual string get_abilities() = 0;
    virtual ~ICharacter() {}
};

class Mario: public ICharacter{
public:
    string get_abilities(){
        return "Mario";
    }
};

class CharacterDecorator: public ICharacter{
protected:
    ICharacter* character;

public:
    CharacterDecorator(ICharacter* character){
        this->character = character;
    }
};

class HeightUp: public CharacterDecorator{
public:
    HeightUp(ICharacter* character) : CharacterDecorator(character){}

    string get_abilities() override{
        return character->get_abilities() + " with Height up";
    }
};

class GunPowerUp: public CharacterDecorator{
public:
    GunPowerUp(ICharacter* character) : CharacterDecorator(character){}

    string get_abilities() override{
        return character->get_abilities() + " with Gun";
    }
};

class StarPowerUp: public CharacterDecorator{
public:
    StarPowerUp(ICharacter* character) : CharacterDecorator(character){}

    string get_abilities() override{
        return character->get_abilities() + " with Star Power(limited time)";
    }

    ~StarPowerUp(){
        cout<<"Destroying StarPowerUp Decorator"<<endl;
    }
};


int main(){
    ICharacter* mario = new Mario();
    cout<<"Basic character: "<< mario->get_abilities()<<endl;

    mario = new HeightUp(mario);
    cout<<"After HeighUp: "<<mario->get_abilities()<<endl;

    mario = new GunPowerUp(mario);
    cout<<"After GunPowerUp: "<<mario->get_abilities()<<endl;

    mario = new StarPowerUp(mario);
    cout<<"After StarPowerUp: "<<mario->get_abilities()<<endl;

    delete mario;
}

