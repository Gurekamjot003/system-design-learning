// SINGLE RESPONSIBILITY PRINCIPLE 

#include<bits/stdc++.h>
using namespace std;

class Product{
public:
    string name;
    double price;

    Product(string name, double price){
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart{
private:
    vector<Product*> products; // 1 shopping cart can have multiple products 1 to many relationship

public:
    void add_product(Product* p){
        products.push_back(p);
    }

    const vector<Product*>& get_products(){
        return products;
    }
    // responsibility 1
    double calculate_total(){
        double ans = 0;
        for(auto& p: products){
            ans += p->price;
        }
        return ans;
    }

    // responsibility 2
    void print_invoice(){
        cout<<"Shopping Cart Invoice: "<<endl;
        for(auto& p: products){
            cout<<p->name<<" - $"<<p->price<<endl;
        }
        cout<<"Total: $"<<calculate_total()<<endl;
    }

    // responsibility 3
    void save_to_database(){
        cout<<"Saving to database..."<<endl;
    }
};

int main(){
    ShoppingCart *cart = new ShoppingCart();
    cart->add_product(new Product("Monitor", 6000));
    cart->add_product(new Product("Mouse", 500));

    cart->print_invoice();
    cart->save_to_database();
}