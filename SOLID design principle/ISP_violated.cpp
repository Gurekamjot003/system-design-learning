// Interface segregation principle

#include<bits/stdc++.h>
using namespace std;

class Shape{
public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Square: public Shape{
private:
    double side;

public:    
    Square(double side){
        this->side = side;
    }

    double area() override{
        return side* side;
    }

    double volume() override{
        throw logic_error("Volume not applicable for squares");
    }
};

class Rectangle: public Shape{
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

    double volume() override{
        throw logic_error("Volume not applicable for rectangles");
    }
};

class Cube: public Shape{
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
    Shape* square = new Square(2);
    Shape* rectangle = new Rectangle(2, 4);
    Shape* cube = new Cube(2);

    cout<<"square area = "<<square->area()<<endl;
    cout<<"rectangle area = "<<rectangle->area()<<endl;
    cout<<"cube area = "<<cube->area()<<endl;
    cout<<"cube volume = "<<cube->volume()<<endl;
    
    cout<<"square volume = "<<square->volume()<<endl;
    cout<<"rectangle volume = "<<rectangle->volume()<<endl;

}