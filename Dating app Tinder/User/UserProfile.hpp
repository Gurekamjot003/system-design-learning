#pragma once
#include "../Location/Location.hpp"
#include "Gender.hpp"
#include "Interest.hpp"

class UserProfile{
    string name;
    int age;
    Gender gender;
    string bio;
    vector<string> photos;
    vector<Interest*> interests;
    Location* location;

    string gender_to_string(){
        string g = "";
        if(gender == Gender::FEMALE) g = "Female";
        else if (gender == Gender::MALE) g = "Male";
        else if (gender == Gender::NON_BINARY) g = "Non-binary";
        else g = "Others";
        return g;
    }
    
    public:
    UserProfile(string name, int age, Gender gender, Location* loc, vector<string> photos = {}, string bio = "", vector<Interest*>  interests = {}): name(name), age(age), gender(gender), location(loc), photos(photos), bio(bio), interests(interests){}
    
    void display(){
        cout<<"\n\nUser Profile\n";
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
        string g = gender_to_string();
        cout<<"Gender: "<< g<<endl;
        cout<<"Bio: "<<bio<<endl;
        cout<<"Location: "<<location->get_latitude()<<", "<<location->get_longitude()<<endl;
        cout<<"Photos: "<<endl;
        for(auto&photo: photos){
            cout<<photo<<endl;
        }
        cout<<"Interests: "<<endl;
        for(auto& interest: interests){
            cout<<interest->get_interest()<<endl;
        }
    }        

    void add_interest(Interest* interest){
        if(interest) interests.push_back(interest);
    }

    void add_photo(string photo){
        photos.push_back(photo);
    }

    void set_bio(string bio){
        this->bio = bio;
    }

    string get_name(){
        return name;
    }

    int get_age(){
        return age;
    }

    Gender get_gender(){
        return gender;
    }

    vector<string> get_photos(){
        return photos;
    }

    vector<Interest*> get_interests(){
        return interests;
    }

    Location* get_location(){
        return location;
    }


    ~UserProfile(){
        delete location;
        for(auto interest: interests) delete interest;
    }


};