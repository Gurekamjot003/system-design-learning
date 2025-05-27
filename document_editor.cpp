#include<bits/stdc++.h>
using namespace std;

class DocumentEditor{
private:   
    vector<string> document_elements;
    string rendered_document;

public:
    void add_text(string text){
        document_elements.push_back(text);
    } 

    void add_image(string image_path){
        document_elements.push_back(image_path);
    }   

    string render_document(){
        if(rendered_document.empty()){
            string result;
            for(auto element: document_elements){
                if(element.size() > 4 && (element.substr(element.size() - 4) == ".jpg" or element.substr(element.size() - 4) == ".png")) 
                    result += "[Image: " + element + "]" + "\n";
                else result += element + "\n";
            }
            rendered_document = result;
        }
        return rendered_document;
    }

    void save_to_file(){
        ofstream file("document.txt");
        if(file.is_open()){
            file<<render_document();
            file.close();
            cout<<"Document saved to document.txt"<<endl;
        }
        else cout<<"Error: Unable to open file"<<endl;

    }
};

int main(){
    DocumentEditor editor;
    editor.add_text("Hello World!");
    editor.add_image("picture.png");
    editor.add_text("This editor was built by me");

    cout<<editor.render_document()<<endl;

    editor.save_to_file();
}