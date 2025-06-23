#include "Zepto.hpp"

int main(){
    Zepto::initialize();

    User* user = new User("Gureakam", 5, 5);
    cout<<"User "<<user->name<<" comes to platform"<<endl;

    Zepto::show_all_items(user);

    cout<<"Adding items to cart"<<endl;
    Cart* cart = user->get_cart();
    cart->add_item(101, 4);    
    cart->add_item(102, 3);    
    cart->add_item(103, 2);   
    
    OrderManager::get_instance()->place_order(user, cart);

    delete user;
}