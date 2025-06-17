#include<bits/stdc++.h>
using namespace std;

class IImage{
public:
    virtual void display() = 0;
    virtual ~IImage() = default;
};

class RealImage: public IImage{
private:
    string path;
public:
    RealImage(string path){
        this->path = path;
        cout<<"[RealImage] Loading image from disk: "<<path<<endl;
    }

    void display() override{
        cout<<"[RealImage] Displaying image "<<path<<endl;
    }
};

class ImageProxy: public IImage{
private:
    RealImage* real_image;
    string path;

public:
    ImageProxy(string path){
        this->path = path;
        real_image = NULL;
    }

    void display() override{
        if(!real_image){
            real_image = new RealImage(path);
        }
        real_image->display();
    }
};

int main(){
    IImage* image = new ImageProxy("butterfly.jpg");
    image->display();
}