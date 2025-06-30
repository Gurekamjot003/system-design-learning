#include<bits/stdc++.h>
using namespace std;

class AsteroidFlyWeight{
private:
    int length, width, weight;
    string material, color;

public:
    friend class AsteroidBuilder;
    
    void render(int x, int y, int dx, int dy){
        cout<<"\nAsteroid: "<<endl;
        cout<<"Length: "<<length<<endl;
        cout<<"Width: "<<width<<endl;
        cout<<"Weight: "<<weight<<endl;
        cout<<"Material: "<<material<<endl;
        cout<<"Color: "<<color<<endl;
        cout<<"Position: "<<x<<","<<y<<endl;
        cout<<"Speed: "<<dx<<","<<dy<<endl;
    }
    
    static size_t calculate_ram(){
        return sizeof(int)*3 
        + (sizeof(string) + 10) *2;
    }
};

class AsteroidBuilder{
    AsteroidFlyWeight* asteroid;

public:
    AsteroidBuilder(){
        asteroid = new AsteroidFlyWeight();
    }
    AsteroidBuilder with_length(int length){
        asteroid->length = length;
        return *this;
    }
    AsteroidBuilder with_width(int width){
        asteroid->width = width;
        return *this;
    }
    AsteroidBuilder with_weight(int weight){
        asteroid->weight = weight;
        return * this;
    }
    AsteroidBuilder with_color(string color){
        asteroid->color = color;
        return * this;
    }
    AsteroidBuilder with_material(string material){
        asteroid->material = material;
        return * this;
    }
    AsteroidFlyWeight* build(){
        return asteroid;
    }
    
};

class AsteroidFactory{
private:
    static map<string, AsteroidFlyWeight*> asteroids;

public:
    static AsteroidFlyWeight* get_asteroid(int length, int width, int weight, string material, string color){
        string cur = to_string(length) 
            + "_" + to_string(width) 
            + "_" + to_string(weight) 
            + "_" + material
            + "_" + color;

        if(asteroids.find(cur) != asteroids.end()) return asteroids[cur];
        return asteroids[cur] = AsteroidBuilder()
            .with_length(length)
            .with_width(width)
            .with_weight(weight)
            .with_material(material)
            .with_color(color)
            .build();
    }

    static size_t calculate_ram(){
        return AsteroidFlyWeight::calculate_ram()*asteroids.size();
    }
    
};

map<string, AsteroidFlyWeight*> AsteroidFactory::asteroids;

class AsteroidContext{
private:
    AsteroidFlyWeight* flyweight;
    int x, y, dx, dy;
    
public:
    AsteroidContext(int x, int y, int dx, int dy, AsteroidFlyWeight* asteroid):x(x), y(y), dx(dx), dy(dy),flyweight(asteroid){

    }

    void render(){
        flyweight->render(x, y, dx, dy);
    }

    size_t calculate_ram(){
        return sizeof(flyweight) + sizeof(int)*4;
    }
};

class SpaceInvader{
    vector<AsteroidContext*> asteroids;
public:
    void add_asteroid(AsteroidContext* asteroid){
        
        asteroids.push_back(asteroid);
    }
    size_t calculate_ram(){
        size_t ans = 0;
        ans = asteroids[0]->calculate_ram();
        ans *= asteroids.size();
        return ans;
    }
    void render(int max_render = INT_MAX){
        cout<<"Rendering the game asteroids"<<endl;
        for(int i = 0; i<(min(max_render, (int)asteroids.size())); i++){
            auto& asteroid = asteroids[i];
            asteroid->render();
        }
    }
    ~SpaceInvader(){
        for(auto& asteroid: asteroids) delete asteroid;
    }
};

int main(){
    vector<int> length = {10, 20, 30};
    vector<int> width = {10, 20, 30};
    vector<int> weight = {50, 100, 200};
    vector<string> material = {"Wood","Plastic", "Metal"};
    vector<string> color = {"Brown", "Red", "Black"};
    
    int ASTEROID_COUNT = 1e6;
    
    SpaceInvader* game = new SpaceInvader();
    for(int i = 0; i<ASTEROID_COUNT; i++){
        int cur_property = i%3;
        
        AsteroidFlyWeight* flyweight =  AsteroidFactory::get_asteroid(
            length[cur_property],
            width[cur_property],
            weight[cur_property],
            material[cur_property],
            color[cur_property]);
                                
        AsteroidContext* asteroid = new AsteroidContext(i*10, i*20, i, i, flyweight);
        game->add_asteroid(asteroid);
    }
    game->render(5);

    cout<<"\n\n\n";
    cout<<"RAM occupied by game: "<<game->calculate_ram()<<" Bytes"<<endl;
    cout<<game->calculate_ram()/(1024.0 * 1024.0)<<" MB"<<endl;
    cout<<"\n\n";
    
    delete game;
}