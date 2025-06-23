#pragma once
#include "../models/Product.hpp"

class IInventoryStore{
public:
    virtual void add_product(Product* product, int quantity) = 0;
    virtual void remove_product(int sku, int quantity) = 0;
    virtual int check_stock(int sku) = 0;
    virtual vector<Product*> list_all_products() = 0;
    virtual ~IInventoryStore(){}
};