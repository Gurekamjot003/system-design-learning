#include <iostream>
using namespace std;

class VendingState; // Forward declaration for base state class

class VendingMachine
{
private:
    VendingState *current_state;
    int item_count, item_price, inserted_coins;

    VendingState *no_coin_state;
    VendingState *has_coin_state;
    VendingState *item_dispense_state;
    VendingState *sold_out_state;

public:
    VendingMachine(int item_count, int item_price);
    void insert_coin(int coin);
    void select_item();
    void dispense();
    void return_coin();
    void refill(int quantity);
    void print_status();

    VendingState *get_no_coin_state();
    VendingState *get_has_coin_state();
    VendingState *get_item_dispense_state();
    VendingState *get_sold_out_state();

    int get_item_count() const;
    void decrease_item_count();
    void increase_item_count(int quantity);

    int get_inserted_coins() const;
    void set_inserted_coins(int coins);
    void add_coin(int coin);
    int get_price();
    void set_price(int price);
};

class VendingState
{
public:
    virtual VendingState *insert_coin(VendingMachine *machine, int coin) = 0;
    virtual VendingState *select_item(VendingMachine *machine) = 0;
    virtual VendingState *dispense(VendingMachine *machine) = 0;
    virtual VendingState *return_coin(VendingMachine *machine) = 0;
    virtual VendingState *refill(VendingMachine *machine, int quantity) = 0;
    virtual string get_state_name() = 0;
};

// ---------------------------- State Implementations ----------------------------

class NoCoinState : public VendingState
{
public:
    VendingState *insert_coin(VendingMachine *machine, int coin) override;
    VendingState *select_item(VendingMachine *machine) override;
    VendingState *dispense(VendingMachine *machine) override;
    VendingState *return_coin(VendingMachine *machine) override;
    VendingState *refill(VendingMachine *machine, int quantity) override;
    string get_state_name() override;
};

class HasCoinState : public VendingState
{
public:
    VendingState *insert_coin(VendingMachine *machine, int coin) override;
    VendingState *select_item(VendingMachine *machine) override;
    VendingState *dispense(VendingMachine *machine) override;
    VendingState *return_coin(VendingMachine *machine) override;
    VendingState *refill(VendingMachine *machine, int quantity) override;
    string get_state_name() override;
};

class ItemDispenseState : public VendingState
{
public:
    VendingState *insert_coin(VendingMachine *machine, int coin) override;
    VendingState *select_item(VendingMachine *machine) override;
    VendingState *dispense(VendingMachine *machine) override;
    VendingState *return_coin(VendingMachine *machine) override;
    VendingState *refill(VendingMachine *machine, int quantity) override;
    string get_state_name() override;
};

class SoldOutState : public VendingState
{
public:
    VendingState *insert_coin(VendingMachine *machine, int coin) override;
    VendingState *select_item(VendingMachine *machine) override;
    VendingState *dispense(VendingMachine *machine) override;
    VendingState *return_coin(VendingMachine *machine) override;
    VendingState *refill(VendingMachine *machine, int quantity) override;
    string get_state_name() override;
};

// ------------------------- State Method Implementations -------------------------

// NoCoinState
VendingState *NoCoinState::insert_coin(VendingMachine *machine, int coin)
{
    machine->add_coin(coin);
    cout << "Coin inserted: " << coin << endl;
    return machine->get_has_coin_state();
}
VendingState *NoCoinState::select_item(VendingMachine *)
{
    cout << "Please insert a coin first." << endl;
    return this;
}
VendingState *NoCoinState::dispense(VendingMachine *)
{
    cout << "Please insert a coin and select an item first." << endl;
    return this;
}
VendingState *NoCoinState::return_coin(VendingMachine *)
{
    cout << "No coins to return." << endl;
    return this;
}
VendingState *NoCoinState::refill(VendingMachine *machine, int quantity)
{
    machine->increase_item_count(quantity);
    cout << "Machine refilled with " << quantity << " items." << endl;
    return this;
}
string NoCoinState::get_state_name()
{
    return "No Coin State";
}

// HasCoinState
VendingState *HasCoinState::insert_coin(VendingMachine *machine, int coin)
{
    machine->add_coin(coin);
    cout << "Adding additional coin: " << coin << endl;
    return this;
}
VendingState *HasCoinState::select_item(VendingMachine *machine)
{
    if (machine->get_inserted_coins() < machine->get_price())
    {
        cout << "Not enough coins inserted. Please insert more coins." << endl;
        return this;
    }
    cout << "Item selected. Dispensing item..." << endl;
    int change = machine->get_inserted_coins() - machine->get_price();
    if (change > 0)
    {
        cout << "Returning change: " << change << endl;
    }
    machine->set_inserted_coins(0);
    return machine->get_item_dispense_state();
}
VendingState *HasCoinState::dispense(VendingMachine *)
{
    cout << "Please select an item first." << endl;
    return this;
}
VendingState *HasCoinState::return_coin(VendingMachine *machine)
{
    cout << "Returning coins: " << machine->get_inserted_coins() << endl;
    machine->set_inserted_coins(0);
    return machine->get_no_coin_state();
}
VendingState *HasCoinState::refill(VendingMachine *machine, int quantity)
{
    machine->increase_item_count(quantity);
    cout << "Machine refilled with " << quantity << " items." << endl;
    return this;
}
string HasCoinState::get_state_name()
{
    return "Has Coin State";
}

// ItemDispenseState
VendingState *ItemDispenseState::insert_coin(VendingMachine *, int)
{
    cout << "Item is being dispensed. Cannot insert coins now." << endl;
    return this;
}
VendingState *ItemDispenseState::select_item(VendingMachine *)
{
    cout << "Item is being dispensed. Cannot select item now." << endl;
    return this;
}
VendingState *ItemDispenseState::dispense(VendingMachine *machine)
{
    cout << "Item dispensed successfully." << endl;
    machine->decrease_item_count();
    if (machine->get_item_count() == 0)
    {
        cout << "Machine is sold out." << endl;
        return machine->get_sold_out_state();
    }
    return machine->get_no_coin_state();
}
VendingState *ItemDispenseState::return_coin(VendingMachine *)
{
    cout << "Item is being dispensed. Cannot return coins now." << endl;
    return this;
}
VendingState *ItemDispenseState::refill(VendingMachine *, int)
{
    cout << "Can't refill in this state" << endl;
    return this;
}
string ItemDispenseState::get_state_name()
{
    return "Item Dispense State";
}

// SoldOutState
VendingState *SoldOutState::insert_coin(VendingMachine *, int)
{
    cout << "Machine is sold out. Cannot insert coins." << endl;
    return this;
}
VendingState *SoldOutState::select_item(VendingMachine *)
{
    cout << "Machine is sold out. Cannot select item." << endl;
    return this;
}
VendingState *SoldOutState::dispense(VendingMachine *)
{
    cout << "Machine is sold out. Cannot dispense item." << endl;
    return this;
}
VendingState *SoldOutState::return_coin(VendingMachine *)
{
    cout << "Machine is sold out. Cannot return coins." << endl;
    return this;
}
VendingState *SoldOutState::refill(VendingMachine *machine, int quantity)
{
    machine->increase_item_count(quantity);
    cout << "Machine refilled with " << quantity << " items." << endl;
    return machine->get_no_coin_state();
}
string SoldOutState::get_state_name()
{
    return "Sold Out State";
}

// ------------------------- VendingMachine Implementation -------------------------

VendingMachine::VendingMachine(int item_count, int item_price)
    : item_count(item_count), item_price(item_price), inserted_coins(0)
{
    no_coin_state = new NoCoinState();
    has_coin_state = new HasCoinState();
    item_dispense_state = new ItemDispenseState();
    sold_out_state = new SoldOutState();

    current_state = item_count > 0 ? no_coin_state : sold_out_state;
}

void VendingMachine::insert_coin(int coin)
{
    current_state = current_state->insert_coin(this, coin);
}
void VendingMachine::select_item()
{
    current_state = current_state->select_item(this);
}
void VendingMachine::dispense()
{
    current_state = current_state->dispense(this);
}
void VendingMachine::return_coin()
{
    current_state = current_state->return_coin(this);
}
void VendingMachine::refill(int quantity)
{
    current_state = current_state->refill(this, quantity);
}
void VendingMachine::print_status()
{
    cout << "\nCurrent State: " << current_state->get_state_name() << endl;
    cout << "Items Available: " << item_count << endl;
    cout << "Item Price: " << item_price << endl;
    cout << "Inserted Coins: " << inserted_coins << "\n"
         << endl;
}

VendingState *VendingMachine::get_no_coin_state() { return no_coin_state; }
VendingState *VendingMachine::get_has_coin_state() { return has_coin_state; }
VendingState *VendingMachine::get_item_dispense_state() { return item_dispense_state; }
VendingState *VendingMachine::get_sold_out_state() { return sold_out_state; }

int VendingMachine::get_item_count() const { return item_count; }
void VendingMachine::decrease_item_count()
{
    if (item_count > 0)
        item_count--;
}
void VendingMachine::increase_item_count(int quantity) { item_count += quantity; }

int VendingMachine::get_inserted_coins() const { return inserted_coins; }
void VendingMachine::set_inserted_coins(int coins) { inserted_coins = coins; }
void VendingMachine::add_coin(int coin) { inserted_coins += coin; }

int VendingMachine::get_price() { return item_price; }
void VendingMachine::set_price(int price) { item_price = price; }

// ------------------------- Main Test -------------------------

int main()
{
    VendingMachine machine(2, 10);

    machine.print_status();
    machine.insert_coin(5); // not enough
    machine.select_item();  // should warn
    machine.insert_coin(5); // now enough
    machine.select_item();  // should accept
    machine.dispense();     // item dispensed
    machine.print_status();

    machine.insert_coin(10);
    machine.select_item();
    machine.dispense();
    machine.print_status();

    machine.insert_coin(5); // should warn sold out
    machine.refill(3);      // refill
    machine.print_status();

    machine.insert_coin(10);
    machine.select_item();
    machine.dispense();
    machine.print_status();
}
