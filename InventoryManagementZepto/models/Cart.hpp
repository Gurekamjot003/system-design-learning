#pragma once
#include "../factories/ProductFactory.hpp"

class Cart{
public:
    vector<pair<Product*, int>> items;

    void add_item(int sku, int quantity){
        Product* p = ProductFactory::create_product(sku);
        items.push_back({p, quantity});
        cout<<"[Cart] Added SKU "<<sku<<" ("<<p->get_name()<<") x"<<quantity<<endl;
    }

    vector<pair<Product*, int>> get_items(){
        return items;
    }

    double get_total(){
        double ans = 0;
        for(auto&[product, quantity]: items){
            ans += product->get_price()*quantity;
        }
        return ans;
    }

    ~Cart(){
        for(auto& it: items) delete it.first;
    }
};