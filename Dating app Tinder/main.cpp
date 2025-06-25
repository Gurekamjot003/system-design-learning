#include "Tinder.hpp"

int main(){
    Tinder* Tinder = Tinder::get_instance();

    Tinder->initialize();
    
    User* Gurekam = Tinder->get_user_by_id("gurekam");
    User* user2 = Tinder->get_user_by_id("user2");

    Gurekam->display_profile();
    user2->display_profile();

    cout<<endl;
    Tinder->display_nearby_users(Gurekam->get_user_id());
    Tinder->display_nearby_users(user2->get_user_id());
    
    Tinder->set_matcher(MatcherType::LOCATION);
    Tinder->swipe(Gurekam->get_user_id(), user2->get_user_id(), SwipeAction::RIGHT);
    Tinder->swipe(user2->get_user_id(), Gurekam->get_user_id(), SwipeAction::RIGHT);
    
    Tinder->send_message(Gurekam->get_user_id(), user2->get_user_id(), "Hi, mujhe to lga tha mai single hi marunga.");
    Tinder->send_message(user2->get_user_id(), Gurekam->get_user_id(), "Hi Gurekam tension mt lo ab mai aa gayi hu.");

    Tinder->display_chat(Gurekam->get_user_id(), user2->get_user_id());
}