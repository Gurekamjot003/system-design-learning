#include<bits/stdc++.h>
using namespace std;

class TextFile;
class ImageFile;
class VideoFile;

class FileSystemVisitor{
public:
    virtual void visit(TextFile* file) = 0;
    virtual void visit(ImageFile* file) = 0;
    virtual void visit(VideoFile* file) = 0;


};

class FileSystem{
    string name;
public:
    FileSystem(string name):name(name){}
    virtual void accept(FileSystemVisitor* visitor) = 0;
    string get_name(){
        return name;
    }
};

class TextFile: public FileSystem{
    string content;
public:
    TextFile(string name, string content):FileSystem(name), content(content){}
    void accept(FileSystemVisitor* visitor) override{
        visitor->visit(this);
    }
    string get_content(){
        return content;
    }
};

class ImageFile: public FileSystem{
    string content;
public:
    ImageFile(string name, string content):FileSystem(name), content(content){}
    void accept(FileSystemVisitor* visitor) override{
        visitor->visit(this);
    }
    string get_content(){
        return content;
    }
};

class VideoFile: public FileSystem{
    string content;
public:
    VideoFile(string name, string content):FileSystem(name), content(content){}
    void accept(FileSystemVisitor* visitor) override{
        visitor->visit(this);
    }
    string get_content(){
        return content;
    }
};

class FileDisplayVisitor: public FileSystemVisitor{
public:
    void visit(TextFile* file) override{
        cout<<"Displaying Text File: "<<file->get_name()<<" - Content: "<<file->get_content()<<endl;
    }
    void visit(ImageFile* file) override{
        cout<<"Displaying Image File: "<<file->get_name()<<" - Content: "<<file->get_content()<<endl;
    }
    void visit(VideoFile* file) override{
        cout<<"Displaying Video File: "<<file->get_name()<<" - Content: "<<file->get_content()<<endl;
    }
};

class FileCompressVisitor: public FileSystemVisitor{
public:
    void visit(TextFile* file) override{
        cout<<"Compressing Text File: "<<file->get_name()<<endl;
    }
    void visit(ImageFile* file) override{
        cout<<"Compressing Image File: "<<file->get_name()<<endl;
    }
    void visit(VideoFile* file) override{
        cout<<"Compressing Video File: "<<file->get_name()<<endl;
    }
};

int main(){
    TextFile* text_file = new TextFile("document.txt", "This is a text document.");
    ImageFile* image_file = new ImageFile("photo.jpg", "JPEG image data.");
    VideoFile* video_file = new VideoFile("movie.mp4", "MP4 video stream.");

    FileDisplayVisitor* display_visitor = new FileDisplayVisitor();
    FileCompressVisitor* compress_visitor = new FileCompressVisitor();

    cout << "--- Displaying Files ---" << endl;
    text_file->accept(display_visitor);
    image_file->accept(display_visitor);
    video_file->accept(display_visitor);

    cout << "\n--- Compressing Files ---" << endl;
    text_file->accept(compress_visitor);
    image_file->accept(compress_visitor);
    video_file->accept(compress_visitor);

    delete text_file;
    delete image_file;
    delete video_file;
    delete display_visitor;
    delete compress_visitor;

    return 0;
}