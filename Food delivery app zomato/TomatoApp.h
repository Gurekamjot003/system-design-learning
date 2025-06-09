#ifndef TOMATO_APP_H
#define TOMATO_APP_H

#include <bits/stdc++.h>
#include "models/User.h"
#include "models/Restaurant.h"
#include "models/Cart.h"
#include "Managers/OrderManager.h"
#include "Managers/RestaurantManager.h"
#include "Strategies/PaymentStrategy.h"
#include "Strategies/UpiPaymentStrategy.h"
#include "Strategies/CreditCardPaymentStrategy.h"
#include "Factories/NowOrderFactory.h"
#include "Factories/ScheduledOrderFactory.h"
#include "Services/NotificationService.h"
#include "Utils/TimeUtils.h"
#include "models/MenuItem.h"
using namespace std;

class TomatoApp {
public:
    TomatoApp() {
        cout << "Welcome to Tomato App!" << endl;
        initialize_restaurants();
    }

    void initialize_restaurants() {
        Restaurant* r1 = new Restaurant("Pizzeria", "Amritsar");
        r1->add_menu_item(MenuItem("P001", "Margherita Pizza", 300));
        r1->add_menu_item(MenuItem("P002", "Pepperoni Pizza", 350));
        r1->add_menu_item(MenuItem("P003", "Veggie Pizza", 320));

        Restaurant* r2 = new Restaurant("Burger King", "Delhi");
        r2->add_menu_item(MenuItem("B001", "Cheese Burger", 200));
        r2->add_menu_item(MenuItem("B002", "Veggie Burger", 180));
        r2->add_menu_item(MenuItem("B003", "Chicken Burger", 220));

        Restaurant* r3 = new Restaurant("Dominoes", "Chandigarh");
        r3->add_menu_item(MenuItem("S001", "Cheese Burst Pizza", 400));
        r3->add_menu_item(MenuItem("S002", "Spicy Paneer Pizza", 450));
        r3->add_menu_item(MenuItem("S003", "Sweet Corn Pizza", 380));

        RestaurantManager::get_instance()->add_restaurant(r1);
        RestaurantManager::get_instance()->add_restaurant(r2);
        RestaurantManager::get_instance()->add_restaurant(r3);
    }

    vector<Restaurant*> search_restaurants(string location){
        return RestaurantManager::get_instance()->search_by_location(location);
    }

    void select_restaurant(User* user, Restaurant* restaurant){
        Cart* cart = user->get_cart();
        cart->set_restaurant(restaurant);
    }

    void add_to_cart(User* user, string item_code){
        Restaurant* restaurant = user->get_cart()->get_restaurant();
        if(!restaurant){
            cout<<"Please set a restaurant first."<<endl;
            return;
        }
        for(auto& item: restaurant->get_menu()){
            if(item.get_code() == item_code){
                user->get_cart()->add_item(item);
                break;
            }
        }
    }

    Order* checkout_now(User* user, string order_type, PaymentStrategy* payment_strategy){
        return checkout(user, order_type, payment_strategy, new NowOrderFactory());
    }

    Order* checkout_scheduled(User* user, string order_type, PaymentStrategy* payment_strategy, string schedule_time){
        return checkout(user, order_type, payment_strategy, new ScheduledOrderFactory(schedule_time));
    }

    Order* checkout(User* user, string order_type, PaymentStrategy* payment_strategy, OrderFactory* order_factory){
        if(user->get_cart()->is_emtpy()) return NULL;

        Cart* user_cart = user->get_cart();
        Restaurant* ordered_restaurant = user_cart->get_restaurant();
        vector<MenuItem> items_ordered = user_cart->get_items();
        double total_cost = user_cart->get_total_cost();

        Order* order = order_factory->create_order(user, user_cart, ordered_restaurant, items_ordered, payment_strategy, total_cost, order_type);
        OrderManager::get_instance()->add_order(order);
        return order;
    }

    void pay_for_order(User* user, Order* order){
        bool is_payment_success = order->process_payment();

        if(is_payment_success){
            NotificationService* notification = new NotificationService();
            notification->notify(order);
            user->get_cart()->clear();
        }
    }

    void print_user_cart(User* user){
        cout<<"Items in cart:"<<endl;
        for(auto& item: user->get_cart()->get_items()){
            cout<<item.get_code()<<": "<<item.get_name()<<": Rs. "<<item.get_price()<<endl;
        }
        cout<<"-------------------------"<<endl;
        cout<<"Grand total: Rs. " << user->get_cart()->get_total_cost()<<endl;
    }
};


#endif