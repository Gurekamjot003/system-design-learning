#include<bits/stdc++.h>
using namespace std;


class DocumentElement{
public:
    virtual string render() = 0;
};

class TextElement: public DocumentElement{
private:
    string text;

public:
    TextElement(string text){
        this->text = text;
    }

    string render() override{
        return text;
    }
};

class ImageElement: public DocumentElement{
private:
    string image_path;

public:
    ImageElement(string image_path){
        this->image_path = image_path;
    }

    string render() override{
        return "[Image: " + image_path + "]";
    }
};

class NewLineElement: public DocumentElement{
public:
    string render() override{
        return "\n";
    }
};

class TabSpaceElement: public DocumentElement{
public:
    string render() override{
        return "\t";
    }
};

class Document{
private:
    vector<DocumentElement*> document_elements;

public:
    void add_element(DocumentElement* element){
        document_elements.push_back(element);
    }

    string render(){
        string result;
        for(auto element: document_elements){
            result += element->render();
        }
        return result;
    }
};

class Persistence{
public:
    virtual void save(string data) = 0;
};

class FileStorage: public Persistence{
public:
    void save(string data) override{
        ofstream outfile("document.txt");
        if(outfile){
            outfile<<data;
            outfile.close();
            cout<<"Document saved to document.txt"<<endl;
        }
        else{
            cout<<"Error: Unable to open file"<<endl;
        }
    }
};

class DBStorage: public Persistence{
public:
    void save(string data) override {
        cout<<"Saved to DB"<<endl;
    }
};

class DocumentEditor{
private:   
    Document* document;
    Persistence* storage;
    string rendered_document;

public:

    DocumentEditor(Document* document, Persistence* storage){
        this->document = document;
        this->storage = storage;
    }

    void add_text(string text){
        document->add_element(new TextElement(text));
    } 

    void add_image(string image_path){
        document->add_element(new ImageElement(image_path));
    }   

    void add_new_line(){
        document->add_element(new NewLineElement);
    }

    void add_tab_space(){
        document->add_element(new TabSpaceElement);
    }

    string render_document(){
        if(rendered_document.empty()){
            rendered_document = document->render();
        }
        return rendered_document;
    }

    void save(){
        storage->save(render_document());
    }
};

int main(){
    Document* document = new Document();
    Persistence* storage = new FileStorage();
    DocumentEditor* editor = new DocumentEditor(document, storage);
    editor->add_text("Hello World!");
    editor->add_new_line();
    editor->add_image("picture.png");
    editor->add_new_line();
    editor->add_tab_space();
    editor->add_text("This editor was built by me and this line has a tabspace");
    editor->add_new_line();

    cout<<editor->render_document()<<endl;

    editor->save();  
}