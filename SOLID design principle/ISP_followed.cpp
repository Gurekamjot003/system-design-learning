// Interface segregation principle

#include<bits/stdc++.h>
using namespace std;

class TwoDimensioalShape{
public:
    virtual double area() = 0;
};

class ThreeDimensioalShape{
public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Square: public TwoDimensioalShape{
private:
    double side;

public:    
    Square(double side){
        this->side = side;
    }

    double area() override{
        return side* side;
    }

};

class Rectangle: public TwoDimensioalShape{
private:
    double length, breadth;

public:    
    Rectangle(double length, double breadth){
        this->length = length;
        this->breadth = breadth;
    }

    double area() override{
        return length* breadth;
    }

};

class Cube: public ThreeDimensioalShape{
private:
    double side;

public:
    Cube(double side){
        this->side = side;
    }

    double area() override{
        return 6*side*side;
    }

    double volume() override{
        return side* side* side;
    }
};

int main(){
    TwoDimensioalShape* square = new Square(2);
    TwoDimensioalShape* rectangle = new Rectangle(2, 4);
    ThreeDimensioalShape* cube = new Cube(2);

    cout<<"square area = "<<square->area()<<endl;
    cout<<"rectangle area = "<<rectangle->area()<<endl;
    cout<<"cube area = "<<cube->area()<<endl;
    cout<<"cube volume = "<<cube->volume()<<endl;

}