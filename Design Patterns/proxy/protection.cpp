#include<bits/stdc++.h>
using namespace std;

class IDocumentReader{
public:
    virtual void unlock_pdf(string file_path, string password) = 0;
    virtual ~IDocumentReader() = default;
};

class RealDocumentReader: IDocumentReader{
public:
    void unlock_pdf(string file_path, string password) override{
        cout<<"[RealDocumnetReader] Unlocking PDF at: "<<file_path<<endl;
        cout<<"[RealDocumnetReader] PDF unlocked successfully with password: "<<password<<endl;
        cout<<"[RealDocumnetReader] Displaying PDF content..."<<endl;
    }
};

class User{
public:
    string name;
    bool is_premium;

    User(string name, bool is_premium){
        this->name = name;
        this->is_premium = is_premium;
    }
};

class DocumentProxy: public IDocumentReader{
private:
    RealDocumentReader* real;
    User* user;

public:
    DocumentProxy(User*user){
        this->user = user;
        real = new RealDocumentReader();
    }

    void unlock_pdf(string file_path, string password) override{
        if(!user->is_premium){
            cout<<"[DocumentProxy] Access denied. Only premium members can unlock PDFs."<<endl;
            return;
        }

        real->unlock_pdf(file_path, password);
    }

    ~DocumentProxy(){
        delete real;
    }
};

int main(){
    User* user1 = new User("Gurekam", true);
    User* user2 = new User("Vansh", false);

    cout<<"-------- Premium Member --------"<<endl;
    IDocumentReader* doc_reader = new DocumentProxy(user1);
    doc_reader->unlock_pdf("notes.pdf", "abcd1234");
    delete doc_reader;

    cout<<endl<<"-------- Non-Premium Member --------"<<endl;
    doc_reader = new DocumentProxy(user2);
    doc_reader->unlock_pdf("notes.pdf", "abcd1234");

    delete doc_reader;
    delete user1;
    delete user2;
}