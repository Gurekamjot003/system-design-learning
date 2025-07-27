#include "Splitwise.hpp"

int main() {
    Splitwise* app = Splitwise::get_instance();

    // Create users
    User* user1 = app->create_user("VT", "vt@gmail.com");
    User* user2 = app->create_user("Rahul", "rahul@gmail.com");
    User* user3 = app->create_user("Ujwal", "ujwal@gmail.com");
    User* user4 = app->create_user("pravinder", "pravinder@gmail.com");
    User* user5 = app->create_user("Sahil", "sahil@gmail.com");
    User* user6 = app->create_user("Gurekam", "gurekam@gmail.com");

    // Create group and add users
    Group* friends = app->create_group("Shareef launde");
    app->add_user_to_group(user1->user_id, friends->group_id);
    app->add_user_to_group(user2->user_id, friends->group_id);
    app->add_user_to_group(user3->user_id, friends->group_id);
    app->add_user_to_group(user4->user_id, friends->group_id);
    app->add_user_to_group(user5->user_id, friends->group_id);
    app->add_user_to_group(user6->user_id, friends->group_id);

    cout << "\n\nAdding expenses in group" << endl;
    vector<string> cake_contri = {user2->user_id, user3->user_id, user4->user_id, user5->user_id, user6->user_id};
    app->add_expense_to_group(friends->group_id, "VT birthday cake", 1500, user2->user_id, cake_contri, SplitType::EQUAL);

    vector<string> birthday_contri = {user1->user_id, user2->user_id, user3->user_id, user4->user_id, user5->user_id, user6->user_id};
    vector<double> amounts = {1500, 100, 100, 100, 100, 100};
    app->add_expense_to_group(friends->group_id, "VT birthday lunch", 2000, user1->user_id, birthday_contri, SplitType::EXACT, amounts);

    cout << "\n\nPrinting group balances" << endl;
    app->show_group_balances(friends->group_id);

    cout << "\n\nDebt Simplification" << endl;
    app->simplify_debts(friends->group_id);

    cout << "\n\nPrinting group balances after simplification" << endl;
    app->show_group_balances(friends->group_id);

    cout << "\n\nAdding individual expense" << endl;
    app->add_individual_expense("Pizza", 100, user2->user_id, user1->user_id, SplitType::EQUAL);

    cout << "\n\nPrinting individual user balances" << endl;
    app->show_user_balance(user1->user_id);
    app->show_user_balance(user2->user_id);
    app->show_user_balance(user3->user_id);
    app->show_user_balance(user4->user_id);
    app->show_user_balance(user5->user_id);
    app->show_user_balance(user6->user_id);

    cout << "\n\nPrinting group balances again after individual expense" << endl;
    app->show_group_balances(friends->group_id);

    return 0;
}
