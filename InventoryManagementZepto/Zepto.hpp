#pragma once
#include "managers/OrderManager.hpp"

class Zepto{
public:
    static void show_all_items(User* user){
        cout<<"[Zepto] All available products within 5 KM for "<<user->name<<":"<<endl;

        DarkStoreManager* dark_store_manager = DarkStoreManager::get_instance();

        vector<DarkStore*> nearby_stores = dark_store_manager->get_nearby_stores(user->x, user->y, 5);

        map<int, pair<string, double>> sku_to_price_n_name;

        for(DarkStore* store: nearby_stores){
            vector<Product*> products = store->get_all_products();
            for(auto product: products){
                int sku = product->get_sku();
                string name = product->get_name();
                double price = product->get_price();
                if(!sku_to_price_n_name.count(sku)){
                    sku_to_price_n_name[sku] = {name, price};
                }
            }
        }

        for(auto it: sku_to_price_n_name){
            int sku = it.first;
            auto[name, price] = it.second;
            cout<<"SKU "<<sku<<" - "<<name<<" Rs."<<price<<endl;
        }
    }

    static void initialize(){
        auto ds_manager = DarkStoreManager::get_instance();

        DarkStore* darkStoreA = new DarkStore("DarkStoreA", 0.0, 0.0, new ThresholdReplenishStrategy(3));
 
        cout << "\nAdding stocks in DarkStoreA...." << endl;  
        darkStoreA->add_stock(101, 5); // Apple
        darkStoreA->add_stock(102, 2); // Banana

        // DarkStore B.......
        DarkStore* darkStoreB = new DarkStore("DarkStoreB", 4.0, 1.0, new ThresholdReplenishStrategy(3));

        cout << "\nAdding stocks in DarkStoreB...." << endl; 
        darkStoreB->add_stock(101, 3); // Apple
        darkStoreB->add_stock(103, 10); // Chocolate

        // DarkStore C.......
        DarkStore* darkStoreC = new DarkStore("DarkStoreC", 2.0, 3.0, new ThresholdReplenishStrategy(3));

        cout << "\nAdding stocks in DarkStoreC...." << endl; 
        darkStoreC->add_stock(102, 5); // Banana
        darkStoreC->add_stock(201, 7); // T-Shirt

        ds_manager->register_dark_store(darkStoreA);
        ds_manager->register_dark_store(darkStoreB);
        ds_manager->register_dark_store(darkStoreC);
    }
};