#include <bits/stdc++.h>
using namespace std;

class DatabaseMomento{
private:
    map<string, string> data;
public:
    DatabaseMomento(const map<string, string>& data){
        this->data = data;
    }
    map<string, string> get_data(){
        return data;
    }

};

class Database{
    map<string, string> data;
public:
    void insert(string key, string value){
        data[key] = value;
        cout<<"Inserting: " << key << " -> " << value << endl;
    }

    void update(string key, string value){
        if(data.find(key) != data.end()){
            data[key] = value;
            cout<<"Updating: " << key << " -> " << value << endl;
        }
        else{
            cout<<"Key not found: " << key << endl;
        }
    }

    void remove(string key){
        if(data.find(key) != data.end()){
            data.erase(key);
            cout<<"Removing: " << key << endl;
        }
        else{
            cout<<"Key not found: " << key << endl;
        }
    }

    DatabaseMomento* create_momento(){
        cout<<"Creating momento"<<endl;
        return new DatabaseMomento(data);
    }

    void restore_from_momento(DatabaseMomento* momento){
        cout<<"Restoring from momento"<<endl;
        data = momento->get_data();
    }

    void display_records(){
        cout<<"\n--- Current Database Records ---"<<endl;
        if(data.empty()){
            cout<<"No records."<<endl;
            return;
        }
        for(auto const& [key, val]: data){
            cout<<key<<" : "<<val<<endl;
        }
        cout<<"--------------------------------"<<endl;
    }
};

class TransactionManager{
    DatabaseMomento* backup;

public:
    TransactionManager():backup(nullptr){}

    ~TransactionManager(){
        if(backup) delete backup;
    }

    void start_transaction(Database* db){
        cout<<"Starting transaction"<<endl;
        if(backup) delete backup;
        backup = db->create_momento();
    }

   void commit_transaction(Database* db){
        cout<<"Committing transaction"<<endl;
        if(backup){
            delete backup; 
            backup = nullptr;
        }
        else{
            cout<<"No transaction to commit"<<endl;
        }
    }

    void rollback_transaction(Database* db){
        cout<<"Rolling back transaction"<<endl;
        if(backup){
            db->restore_from_momento(backup);
            delete backup;
            backup = nullptr;
        }
        else{
            cout<<"No transaction to rollback"<<endl;
        }
    }

};

int main(){
    Database* db = new Database();
    TransactionManager* manager = new TransactionManager();

    manager->start_transaction(db);
    db->insert("gurekam", "gurekam@email.com");
    db->insert("vt", "vt@email.com");
    manager->commit_transaction(db);
    db->display_records();

    manager->start_transaction(db);
    db->insert("ravneet", "r@email.com");
    db->remove("vt");
    db->display_records();

    cout<<"Error occurred"<<endl;
    manager->rollback_transaction(db);
    db->display_records();
}