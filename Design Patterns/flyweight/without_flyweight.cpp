#include<bits/stdc++.h>
using namespace std;

class Asteroid{
private:
    int length, width, weight;
    string material, color;
    int x, y, dx, dy;

public:
    friend class AsteroidBuilder;
    
    void render(){
        cout<<"\nAsteroid: "<<endl;
        cout<<"Length: "<<length<<endl;
        cout<<"Width: "<<width<<endl;
        cout<<"Weight: "<<weight<<endl;
        cout<<"Material: "<<material<<endl;
        cout<<"Color: "<<color<<endl;
        cout<<"Position: "<<x<<","<<y<<endl;
        cout<<"Speed: "<<dx<<","<<dy<<endl;
    }
};

class SpaceInvader{
    vector<Asteroid*> asteroids;
public:
    void add_asteroid(Asteroid* asteroid){
        
        asteroids.push_back(asteroid);
    }
    size_t calculate_ram(){
        size_t ans = 0;
        ans = sizeof(int)*3
            + (sizeof(string)+10)*2
            + sizeof(int)*4;
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

class AsteroidBuilder{
    Asteroid* asteroid;

public:
    AsteroidBuilder(){
        asteroid = new Asteroid();
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
    AsteroidBuilder with_position(int x, int y){
        asteroid->x = x;
        asteroid->y = y;
        return * this;
    }
    AsteroidBuilder with_speed(int dx, int dy){
        asteroid->dx = dx;
        asteroid->dy = dy;
        return * this;
    }
    Asteroid* build(){
        return asteroid;
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
        
        Asteroid* asteroid = AsteroidBuilder()
                                .with_length(length[cur_property])
                                .with_width(width[cur_property])
                                .with_weight(weight[cur_property])
                                .with_material(material[cur_property])
                                .with_color(color[cur_property])
                                .with_position(i*10, i*20)
                                .with_speed(i, i)
                                .build();
        game->add_asteroid(asteroid);
    }
    game->render(5);

    cout<<"\n\n\n";
    cout<<"RAM occupied by game: "<<game->calculate_ram()<<" Bytes"<<endl;
    cout<<game->calculate_ram()/(1024.0 * 1024.0)<<" MB"<<endl;
    cout<<"\n\n";
    
    delete game;
}