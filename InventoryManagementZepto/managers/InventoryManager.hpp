#pragma once
#include "../inventry stores/DbInventoryStore.hpp"
#include "../factories/ProductFactory.hpp"

class InventoryManager{
    IInventoryStore* store;

public: 

    InventoryManager(IInventoryStore* store){
        this->store = store;
    }

    void add_stock(int sku, int quantity){
        Product* product = ProductFactory::create_product(sku);
        store->add_product(product, quantity);
        cout<<"[InventoryManager] Added SKU "<<sku<<" Quantity "<<quantity<<endl;
    }

    void remove_stock(int sku, int quantity){
        store->remove_product(sku, quantity);
    }

    int check_stock(int sku){
        return store->check_stock(sku);
    }

    vector<Product*> get_available_products(){
        return store->list_all_products();
    }
};