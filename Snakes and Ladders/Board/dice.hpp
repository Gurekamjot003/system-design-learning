#pragma once
#include <bits/stdc++.h>
using namespace std;

class Dice{
    int faces;
public:
    Dice(int faces = 6) : faces(faces) {
        if (faces < 1) {
            throw invalid_argument("Dice must have at least one face");
        }
    }
    int roll() {
        return rand() % faces + 1; // Returns a random number between 1 and faces
    }
};