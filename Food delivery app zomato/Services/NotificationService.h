#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include<bits/stdc++.h>
#include "../models/Order.h"
using namespace std;

class NotificationService {
public:
    static void notify(Order* order) {
        if (order) {
            cout << "Notification: New " << order->get_type() << " order placed!"<<endl
                 << "Order ID: " << order->get_order_id()<<endl 
                 << "Customer: " << order->get_user()->get_name() << endl
                 << "Restaurant: " << order->get_restaurant()->get_name() << endl
                 << "Items: "<<endl;

            for (auto item : order->get_items()) {
                cout << "- " << item.get_name() << " (Rs. " << item.get_price() << ")" << endl;
            }
            cout << "Total Cost: Rs. " << order->get_total() << endl
                 << "Scheduled At: " << order->get_schedule() << endl;
            cout<< "Payment: Done"<<endl;

        } else {
            cout << "Notification: Order placement failed." << endl;
        }
    }
};

#endif