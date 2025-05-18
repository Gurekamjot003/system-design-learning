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

};

class ShoppingCartPrinter{
    private:
    ShoppingCart* cart; // has a relationship

    public:
    ShoppingCartPrinter(ShoppingCart* cart){
        this->cart = cart;
    }

    void print_invoice(){
        cout<<"Shopping Cart Invoice: "<<endl;
        for(auto& p: cart->get_products()){
            cout<<p->name<<" - $"<<p->price<<endl;
        }
        cout<<"Total: $"<<cart->calculate_total()<<endl;
    }
    
};

class ShoppingCartStorage{
    private:
    ShoppingCart* cart; // has a relationship

    public:
    ShoppingCartStorage(ShoppingCart* cart){
        this->cart = cart;
    }

    void save_to_database(){
        cout<<"Saving to database..."<<endl;
    }
};

int main(){
    ShoppingCart *cart = new ShoppingCart();
    cart->add_product(new Product("Monitor", 6000));
    cart->add_product(new Product("Mouse", 500));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->print_invoice();

    ShoppingCartStorage* db = new ShoppingCartStorage(cart);
    db->save_to_database();
}