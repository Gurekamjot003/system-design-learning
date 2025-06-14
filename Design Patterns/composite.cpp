#include<bits/stdc++.h>
using namespace std;

class FileSystem{
public:
    virtual void ls(int indent = 0) = 0;
    virtual void open_all(int indent = 0) = 0;
    virtual int get_size() = 0;
    virtual string get_name() = 0;
    virtual FileSystem* cd(string name) = 0;
    virtual bool is_folder() = 0;
    virtual ~FileSystem(){}
};

class File: public FileSystem{
private:   
    string name;
    int size;

public:
    File(string name, int size){
        this->name = name;
        this->size = size;
    }
    
    void ls(int indent = 0) override{
        cout<<string(indent, ' ') <<name<<endl;
    }

    void open_all(int indent = 0) override{
        cout<<string(indent, ' ') <<name<<endl;
    }

    int get_size() override{
        return size;
    }

    FileSystem* cd(string loc) override{
        return NULL;
    }

    bool is_folder() override{
        return false;
    }

    string get_name()override{
        return name;
    }
};

class Folder: public FileSystem{
private:
    string name;
    vector<FileSystem*> children;

public:
    Folder(string name){
        this->name = name;
    }

    ~Folder(){
        for(auto& c: children) delete c;
    }
    void add(FileSystem* item){
        children.push_back(item);
    }

    void ls(int indent = 0) override{
        for(auto child: children){
            if(child->is_folder()){
                cout<<string(indent, ' ')<<"+ "<<child->get_name()<<endl;
            }
            else{
                cout<<string(indent, ' ')<<child->get_name()<<endl;
            }
        }
    }

    string get_name() override{
        return name;
    }

    bool is_folder() override{
        return true;
    }

    void open_all(int indent = 0) override{
        cout<<string(indent, ' ')<<"+ "<<name<<endl;
        for(auto child: children){
            child->open_all(indent + 4);
        }  
    }

    int get_size() override{
        int size = 0;
        for(auto child: children){
            size += child->get_size();
        }
        return size;
    }

    FileSystem* cd(string loc) override{
        for(auto child: children){
            if(child->is_folder() && child->get_name() == loc) return child;
        }
        return NULL;
    }

};

int main(){
    Folder* root = new Folder("root");

    root->add(new File("file1.txt", 1));
    root->add(new File("file2.txt", 1));

    Folder* docs = new Folder("docs");
    root->add(docs);
    docs->add(new File("resume.pdf", 1));
    docs->add(new File("document.txt", 1));

    Folder* images = new Folder("images");
    root->add(images);
    images->add(new File("image.png", 10));

    cout<<"\nroot - ls"<<endl;
    root->ls();
    
    cout<<"\ndoc - ls"<<endl;
    docs->ls();
    
    cout<<"\nroot - open_all"<<endl;
    root->open_all();
    
    cout<<"\nroot - size"<<endl;
    cout<<root->get_size()<<endl;
    delete root;
}