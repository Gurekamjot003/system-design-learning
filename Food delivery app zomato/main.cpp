#include<bits/stdc++.h>
#include "TomatoApp.h"
using namespace std;

int main(){
    TomatoApp* tomato = new TomatoApp();

    User* user = new User(111, "Gurekamjot", "Amritsar");
    cout<<"User: "<<user->get_name()<<" is active."<<endl;

    vector<Restaurant*> restaurant_list = tomato->search_restaurants("Amritsar");
    if(restaurant_list.empty()){
        cout<<"No restaruants found"<<endl;
        return 0;
    }
    cout<<"Restaurants found"<<endl;
    for(auto& restaurant: restaurant_list){
        cout<<" - " <<restaurant->get_name()<<endl;
    }

    tomato->select_restaurant(user, restaurant_list[0]);   
    cout<<"Selected restaurant: "<<restaurant_list[0]->get_name()<<endl;

    tomato->add_to_cart(user, "P001");
    tomato->add_to_cart(user, "P002");

    tomato->print_user_cart(user);

    Order* order = tomato->checkout_now(user, "Delivery", new UpiPaymentStrategy("1234567890"));

    tomato->pay_for_order(user, order);

    delete tomato;
    delete user;

    return 0;
}