#pragma once
#include "Gender.hpp"
#include "Interest.hpp"
#include<bits/stdc++.h>
using namespace std;

class Preference{
    int max_age;
    int min_age;
    double max_distance;
    unordered_set<string> interests;
    unordered_set<Gender> interested_in;

public:
    Preference(int min_age, int max_age, double max_distance, unordered_set<string> interests = {}, unordered_set<Gender> interested_in = {}):min_age(min_age), max_age(max_age), max_distance(max_distance), interests(interests), interested_in(interested_in){}

    void add_interest(string interest){
        interests.insert(interest);
    }

    void add_gender_interest(Gender gender){
        interested_in.insert(gender);
    }

    bool check_age(int age){
        return age>=min_age && age<=max_age;
    }

    bool check_distance(double distance){
        return distance<=max_distance;
    }

    bool check_interest(Interest* interest){
        return interests.count(interest->get_name());
    }

    bool check_interested_in(Gender gender){
        return interested_in.count(gender);
    }

    double get_max_distance(){
        return max_distance;
    }

    ~Preference(){
    }
};