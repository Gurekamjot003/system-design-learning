#pragma once
#include"IInventoryStore.hpp"

class DbInventoryStore: public IInventoryStore{
    map<int, int> stocks;
    map<int, Product*> products;

public:
    DbInventoryStore(){}
    ~DbInventoryStore(){
        for(auto& it: products) delete it.second;
    }

    void add_product(Product* product, int quantity) override{
        int sku = product->get_sku();
        if(products.find(sku) != products.end()){
            delete product;
        }
        else products[sku] = product;
        stocks[sku] += quantity;
    }

    void remove_product(int sku, int quantity){
        if(stocks.find(sku) == stocks.end()) return;
        
        stocks[sku] -= quantity;
        if(stocks[sku]<=0){
            stocks.erase(sku);
        }
    }

    int check_stock(int sku) override{
        return stocks[sku];
    }

    vector<Product*> list_all_products() override{
        vector<Product*> ans;
        for(auto& it: products){
            if(stocks[it.first]>0) ans.push_back(it.second);
        }
        return ans;
    }
};