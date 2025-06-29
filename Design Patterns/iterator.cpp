#include<bits/stdc++.h>
using namespace std;

template<class T>
class Iterator{
public:
    virtual bool has_next() = 0;
    virtual T next() = 0;
};

template<class T>
class Iterable{
public:
    virtual Iterator<T>* get_iterator() = 0;
};

class LinkedList: public Iterable<int>{
public:
    int data;
    LinkedList* next;

    LinkedList(int data):data(data), next(NULL){}

    Iterator<int>* get_iterator() override;
};

class BinaryTree: public Iterable<int>{
public:
    int data;
    BinaryTree* left,*right;

    BinaryTree(int data):data(data),left(NULL),right(NULL){}

    Iterator<int>* get_iterator() override;
};

class Song{
public:
    string title, artist;
    Song(string title, string artist):title(title),artist(artist){}
};

class Playlist: public Iterable<Song>{
public:     
    vector<Song> songs;

    void add_song(Song song){
        songs.push_back(song);
    }

    Iterator<Song>* get_iterator() override;
};

class LinkedListIterator:public Iterator<int>{
public:
    LinkedList* cur;

    LinkedListIterator(LinkedList* head):cur(head){}

    bool has_next() override{
        if(!cur) return false;
        return true;
    }

    int next() override{
        if(!has_next()) throw runtime_error("Null pointer access exception");
        int val =  cur->data;
        cur = cur->next;
        return val;
    }
};

class BinaryTreeIterator: public Iterator<int>{
public:
    queue<BinaryTree*> q;

    BinaryTreeIterator(BinaryTree* root){
        while(!q.empty()) q.pop();
        if(root)
            q.push(root);
    }

    bool has_next() override{
        return !q.empty();
    }

    int next() override{
        if(!has_next()) throw runtime_error("Null Pointer access exception");
        BinaryTree* cur = q.front();
        q.pop();
        if(cur->left) q.push(cur->left);
        if(cur->right) q.push(cur->right);
        return cur->data;
    }
};

class PlaylistIterator: public Iterator<Song>{
public:
    Playlist* playlist;
    int ptr;

    PlaylistIterator(Playlist* playlist):playlist(playlist),ptr(0){}

    bool has_next() override{
        if(!playlist) return false;
        if(ptr>=playlist->songs.size()) return false;
        return true;
    }

    Song next() override{
        if(!has_next()) throw runtime_error("Null pointer access exception");
        return playlist->songs[ptr++];
    }
};

Iterator<int>* LinkedList::get_iterator(){
    return new LinkedListIterator(this);
}
Iterator<int>* BinaryTree::get_iterator(){
    return new BinaryTreeIterator(this);
}
Iterator<Song>* Playlist::get_iterator(){
    return new PlaylistIterator(this);
}


int main(){
    LinkedList* ll = new LinkedList(1);
    ll->next = new LinkedList(2);
    ll->next->next = new LinkedList(3);

    cout<<"\n\nLINKED LIST\n\n";
    Iterator<int>* it1 = new LinkedListIterator(ll);
    while(it1->has_next()){
        cout<<it1->next()<<endl;
    }
    
    BinaryTree* bt = new BinaryTree(2);
    bt->left = new BinaryTree(1);
    bt->right = new BinaryTree(3);

    cout<<"\n\nBINARY TREE\n\n";
    Iterator<int>* it2 = new BinaryTreeIterator(bt);
    while(it2->has_next()){
        cout<<it2->next()<<endl;
    }

    Playlist* my_playlist = new Playlist();
    my_playlist->add_song(Song("Kesariya", "Arijit Singh"));
    my_playlist->add_song(Song("295", "Sidhu Moose Wala"));
    
    cout<<"\n\nPLAYLIST\n\n";
    Iterator<Song>* it3 = new PlaylistIterator(my_playlist);
    while(it3->has_next()){
        Song song = it3->next();
        cout<<song.title<<" - By "<<song.artist<<endl;
    }
    
}