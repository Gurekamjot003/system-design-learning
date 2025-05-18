//OPEN CLOSE PRINCIPLE
// open for extension, closed for modification

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

//abstract class
class persistence{
    private: 
    ShoppingCart* cart;

    public:
    virtual void save(ShoppingCart* cart) = 0;
};

class SQL_persistance: public persistence{
    public:
    void save(ShoppingCart* cart) override{
        cout<<"Saving to SQL database..."<<endl;
    }
};

class mongo_persistance: public persistence{
    public:
    void save(ShoppingCart* cart) override{
        cout<<"Saving to mongo database..."<<endl;
    }
};

class file_persistance: public persistence{
    public:
    void save(ShoppingCart* cart) override{
        cout<<"Saving to file..."<<endl;
    }
};

int main(){
    ShoppingCart *cart = new ShoppingCart();
    
    cart->add_product(new Product("Monitor", 6000));
    cart->add_product(new Product("Mouse", 500));

    ShoppingCartPrinter* printer = new ShoppingCartPrinter(cart);
    printer->print_invoice();

    persistence* db = new SQL_persistance();
    persistence* mongo = new mongo_persistance();
    persistence* file = new file_persistance();

    db->save(cart);
    mongo->save(cart);
    file->save(cart);
}