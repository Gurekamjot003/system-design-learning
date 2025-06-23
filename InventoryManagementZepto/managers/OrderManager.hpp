#pragma once
#include "DarkStoreManager.hpp"
#include "../models/Order.hpp" 

class OrderManager{
    vector<Order*> orders;
    static OrderManager* instance;
    OrderManager(){}
public:
    static OrderManager* get_instance(){
        if(!instance) instance = new OrderManager();
        return instance;
    }
    void place_order(User* user, Cart* cart) {
        cout << "[OrderManager] Placing order for: " << user->name << endl;

        DarkStoreManager* ds_manager = DarkStoreManager::get_instance();
        vector<DarkStore*> nearby_stores = ds_manager->get_nearby_stores(user->x, user->y, 5);
        auto cart_items = cart->get_items();

        // Calculate required quantities
        map<int, int> required_qty;
        for (auto& [product, qty] : cart_items) {
            required_qty[product->get_sku()] += qty;
        }
        int total_required_units = 0;
        for (auto& [sku, qty] : required_qty) total_required_units += qty;

        struct Plan {
            map<DarkStore*, map<int,int>> allocation;
            set<DarkStore*> used_stores;
            int units_fulfilled;
            double total_distance;

            bool better_than(const Plan& o) const {
                if (units_fulfilled != o.units_fulfilled)
                    return units_fulfilled > o.units_fulfilled;
                if (used_stores.size() != o.used_stores.size())
                    return used_stores.size() < o.used_stores.size();
                return total_distance < o.total_distance;
            }
        };

        Plan best_plan{{}, {}, 0, 0.0};
        bool found = false;
        int n = nearby_stores.size();

        // Enumerate all non-empty subsets of stores
        for (int mask = 1; mask < (1<<n); ++mask) {
            vector<DarkStore*> subset;
            double dist = 0.0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1<<i)) {
                    subset.push_back(nearby_stores[i]);
                    auto [sx, sy] = nearby_stores[i]->get_coordinate();
                    dist += sqrt((sx-user->x)*(sx-user->x) + (sy-user->y)*(sy-user->y));
                }
            }

            // Try to allocate from this subset
            map<int,int> rem = required_qty;
            map<DarkStore*, map<int,int>> alloc;
            int fulfilled = 0;

            for (auto* store : subset) {
                for (auto& [sku, req] : required_qty) {
                    if (rem[sku] == 0) continue;
                    int stock = store->check_stock(sku);
                    int take = min(rem[sku], stock);
                    if (take > 0) {
                        alloc[store][sku] += take;
                        rem[sku] -= take;
                        fulfilled += take;
                    }
                }
            }

            if (fulfilled == 0) continue; // skip useless subsets

            Plan p{alloc, {}, fulfilled, dist};
            for (auto& [store, _] : alloc) p.used_stores.insert(store);

            if (!found || p.better_than(best_plan)) {
                best_plan = move(p);
                found = true;
            }
        }

        if (!found) {
            cout << " -> [Order Failed] No stock available in any nearby store." << endl;
            return;
        }

        // Report shortages
        map<int,int> got_qty;
        for (auto& [store, skus] : best_plan.allocation)
            for (auto& [sku, q] : skus)
                got_qty[sku] += q;

        bool partial = false;
        for (auto& [product, req] : cart_items) {
            int sku = product->get_sku();
            if (got_qty[sku] < req) {
                partial = true;
                cout << " -> [Partial Fulfill] SKU " << sku
                    << " (" << product->get_name()
                    << ") short by " << (req - got_qty[sku]) << " unit(s)" << endl;
            }
        }

        // Deduct stock & replenish
        for (auto& [store, skus] : best_plan.allocation) {
            cout << " - From " << store->get_name() << ":" << endl;
            for (auto& [sku, q] : skus) {
                store->remove_stock(sku, q);
                cout << "   -> Deducted SKU " << sku << " x" << q << endl;
            }
            store->run_replenish(skus);
        }

        // Build and save the actual Order
        Order* order = new Order(user);
        double bill = 0.0;
        for (auto& [product, req] : cart_items) {
            int sku = product->get_sku();
            int used = got_qty[sku];
            if (used > 0) {
                Product* p = ProductFactory::create_product(sku);
                order->items.push_back({p, used});
                bill += p->get_price() * used;
            }
        }
        order->total = bill;
        orders.push_back(order);

        if (partial) {
            cout << "[OrderManager] Partial order placed. Total Rs." << order->total << endl;
        } else {
            cout << "[OrderManager] Order ID " << order->order_id
                << " placed successfully. Total Rs." << order->total << endl;
        }
    }


    vector<Order*> get_all_orders(){
        return orders;
    }

    ~OrderManager(){
        for(auto order: orders) delete order;
    }
};

OrderManager* OrderManager::instance = NULL;