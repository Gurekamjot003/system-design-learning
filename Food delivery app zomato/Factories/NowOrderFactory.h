#ifndef NOW_ORDER_FACTORY_H
#define NOW_ORDER_FACTORY_H

#include "OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../Utils/TimeUtils.h"
using namespace std;

class NowOrderFactory: public OrderFactory{
public:
    Order* create_order(User* user, Cart* cart, Restaurant* restaurant, vector<MenuItem> menu_items, PaymentStrategy* payment_strategy, double total_cost, string order_type) override{
        Order* order = NULL;
        if(order_type == "Delivery"){
            auto delivery_order = new DeliveryOrder();
            delivery_order ->set_user_address(user->get_address());
            order = delivery_order;
        }
        else{
            auto pickup_order = new PickupOrder();
            pickup_order->set_restaurant_address(restaurant->get_location());
            order = pickup_order;
        }

        order->set_user(user);
        order->set_items(menu_items);
        order->set_payment_strategy(payment_strategy);
        order->set_restaurant(restaurant);
        order->set_total(total_cost);
        order->set_scheduled(TimeUtils::get_current_time());
        return order;
    }
};

#endif