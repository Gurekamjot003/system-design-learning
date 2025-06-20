#include<bits/stdc++.h>
using namespace std;

class Product{
private:
    string name;
    string category;
    double price;

public:
    Product(string name, string category, double price): name(name), category(category), price(price){}

    double get_price(){
        return price;
    }

    string get_category(){
        return category;
    }
};

class CartItem{
private:
    Product* product;
    int quantity;

public:
    CartItem(Product* product, int quantity){
        this->product = product;
        this->quantity = quantity;
    }
    double item_total(){
        return product->get_price() * quantity;
    }

    int get_quantity(){
        return quantity;
    }

    void set_quantity(int quantity){
        this->quantity = quantity;
    }

    Product* get_product(){
        return product;
    }
};

class Cart{
private:
    vector<CartItem*> items;
    bool loyalty_member;
    double intital_total;
    double final_total;
    string payment_bank;

public:
    Cart(){
        intital_total = final_total = 0;
        loyalty_member = false;
        items = {};
        payment_bank = "";
    }
    void add_product(Product* product, int quantity){
        CartItem* item = new CartItem(product, quantity);
        items.push_back(item);
        intital_total += item->item_total();
        final_total += item->item_total();
    }

    double get_initial_total(){
        return intital_total;
    }

    double get_final_total(){
        return final_total;
    }

    void apply_discount(double discount){
        final_total -= discount;
        final_total = max(final_total, 0.0);
    }

    void set_loyalty_member(bool loyalty){
        this->loyalty_member = loyalty;
    }

    bool is_loyalty_member(){
        return loyalty_member;
    }

    void set_payment_bank(string bank){
        this->payment_bank = bank;
    }

    string get_payment_bank(){
        return payment_bank;
    }

    vector<CartItem*> get_items(){
        return items;
    }
};

enum class StrategyType{
    FLAT,
    PERCENT,
    PRCENT_WITH_CAP
};

class DiscountStrategy{
public:
    virtual double calculate(double base_amount) = 0;
    virtual ~DiscountStrategy(){}
};

class FlatDiscountStrategy: public DiscountStrategy{
    double amount;
    
public:
    FlatDiscountStrategy(double amount){
        this->amount = amount;
    }

    double calculate(double base_amount) override{
        return min(base_amount, amount);
    }
};

class PercentDiscountStrategy: public DiscountStrategy{
    double percentage;

    
public:
    PercentDiscountStrategy(double percent){
        this->percentage = percent;
    }

    double calculate(double base_amount) override{
        return base_amount*percentage/100.000;
    }
};

class PercentageWithCapDiscountStrategy: public DiscountStrategy{
    double max_discount;
    double percent;
    
public:
    PercentageWithCapDiscountStrategy(double max_discount, double percent){
        this->max_discount = max_discount;
        this->percent = percent;
    }

    double calculate(double base_amount) override{
        double discount = base_amount * percent/100.0;
        return min(max_discount, discount);
    }
};

class DiscountStrategyManager{
private:
    static DiscountStrategyManager* instance;
    DiscountStrategyManager(){}

public:
    static DiscountStrategyManager* get_instance(){
        if(!instance) instance = new DiscountStrategyManager();
        return instance;
    }

    DiscountStrategy* get_strategy(StrategyType strategy, double param1, double param2 = 0){
        if(strategy == StrategyType::FLAT){
            return new FlatDiscountStrategy(param1);
        }
        else if(strategy == StrategyType::PERCENT){
            return new PercentDiscountStrategy(param1);
        }
        return new PercentageWithCapDiscountStrategy(param1, param2);
    }
};

DiscountStrategyManager* DiscountStrategyManager::instance = NULL;

class Coupon{
protected:
    Coupon* next;

public:
    Coupon(){
        next = NULL;
    }

    void set_next(Coupon* next){
        this->next = next;
    }

    Coupon* get_next(){
        return this->next;
    }

    virtual bool is_applicable(Cart* cart) = 0;
    virtual double get_discount(Cart* cart) = 0;
    virtual bool is_combinable(){
        return true;
    }

    void apply_discount(Cart* cart){
        if(is_applicable(cart)){
            double discount = get_discount(cart);
            cart->apply_discount(discount);
            cout<<name()<<" applied: "<<discount<<endl;
            if(!is_combinable()) return;
        }
        if(next) next->apply_discount(cart);
    }

    virtual string name() = 0;

    virtual ~Coupon(){
        if(next) delete next;
    }
};

class SeasonalOffer: public Coupon{
private:
    double percent;
    string category;
    DiscountStrategy* strategy;

public:
    SeasonalOffer(double percent, string category){
        this->percent = percent;
        this->category = category;
        strategy = DiscountStrategyManager::get_instance()->get_strategy(StrategyType::PERCENT, percent);
    }

    ~SeasonalOffer(){
        delete strategy;
    }

    bool is_applicable(Cart* cart) override{
        for(auto& item: cart->get_items()){
            if(item->get_product()->get_category() == category){
                return true;
            }
        }
        return false;
    }

    double get_discount(Cart* cart) override{
        double subtotal = 0.0;
        for(auto& item: cart->get_items()){
            if(item->get_product()->get_category() == category){
                subtotal += item->item_total();
            }
        }
        return strategy->calculate(subtotal);
    }

    bool is_combinable() override{
        return true;
    }

    string name() override{
        return "Seasonal offer " + to_string((int)percent) + " \% off " + category;
    }
};

class LoyaltyDiscount: public Coupon{
private:
    double percent;
    DiscountStrategy* strategy;

public:
    LoyaltyDiscount(double percent){
        this->percent = percent;
        strategy = DiscountStrategyManager::get_instance()->get_strategy(StrategyType::PERCENT, percent);
    }

    ~LoyaltyDiscount(){
        delete strategy;
    }

    bool is_applicable(Cart* cart) override{
        return cart->is_loyalty_member();
    }

    double get_discount(Cart* cart) override{
        return strategy->calculate(cart->get_final_total());
    }

    string name() override{
        return "Loyalty offer " + to_string((int)percent) + " \% off " ;
    }
};

class BulkPurchaseDiscount: public Coupon{
private:
    double threshold;
    double flat_off;
    DiscountStrategy* strategy;

public:
    BulkPurchaseDiscount(double threshold, double flat_off){
        this->threshold = threshold;
        this->flat_off = flat_off;
        strategy = DiscountStrategyManager::get_instance()->get_strategy(StrategyType::FLAT, flat_off);
    }

    ~BulkPurchaseDiscount(){
        delete strategy;
    }

    bool is_applicable(Cart* cart) override{
        return cart->get_initial_total() >= threshold;
    }

    double get_discount(Cart* cart) override{
        return strategy->calculate(cart->get_final_total());
    }

    string name() override{
        return "Bulk Purchase offer flat " + to_string((int)flat_off) + " off " ;
    }
};

class BankingCoupon: public Coupon{
private:
    string bank;
    double min_spend;
    double flat_off;
    double percent;
    DiscountStrategy* strategy;

public:
    BankingCoupon(double min_spend, double flat_off, double percent, string bank){
        this->min_spend = min_spend;
        this->flat_off = flat_off;
        this->percent = percent;
        this->bank = bank;
        strategy = DiscountStrategyManager::get_instance()->get_strategy(StrategyType::PRCENT_WITH_CAP, flat_off, percent);
    }

    ~BankingCoupon(){
        delete strategy;
    }

    bool is_applicable(Cart* cart) override{
        return cart->get_initial_total() >= min_spend && cart->get_payment_bank() == bank;
    }

    double get_discount(Cart* cart) override{
        return strategy->calculate(cart->get_final_total());
    }

    string name() override{
        return "Bank offer " + to_string((int)percent) + " \% off upto Rs. " + to_string((int)flat_off);
    }
};

class CouponManager{
    Coupon* head;
    mutable mutex mtx;
    static CouponManager* instance;
    CouponManager(){
        head = NULL;
    }

public: 
    static CouponManager* get_instance(){
        if(!instance) instance = new CouponManager();
        return instance;
    }

    void register_coupon(Coupon* coupon){
        if(!coupon) return;
        lock_guard<mutex> lock(mtx);
        if(!head) head = coupon;
        else{
            Coupon* cur = head;
            while(cur->get_next()) cur = cur->get_next();
            cur->set_next(coupon);
        }
    }

    vector<string> get_applicable_coupons(Cart* cart){
        lock_guard<mutex> lock(mtx);
        vector<string> ans;
        Coupon* cur = head;
        while(cur){
            if(cur->is_applicable(cart)){
                ans.push_back(cur->name());
            }
            cur = cur->get_next();
        }
        return ans;
    }

    double apply_all(Cart* cart){
        lock_guard<mutex> lock(mtx);
        if(head){
            head->apply_discount(cart);
        }
        return cart->get_final_total();
    }
};

CouponManager* CouponManager::instance = NULL;

int main(){
    CouponManager* manager = CouponManager::get_instance();
    manager->register_coupon(new SeasonalOffer(10, "Clothing"));
    manager->register_coupon(new LoyaltyDiscount(5));
    manager->register_coupon(new BulkPurchaseDiscount(1000, 100));
    manager->register_coupon(new BankingCoupon(2000, 500, 15, "HDFC"));
    
    Product* p1 = new Product("Jacket", "Clothing", 1000);
    Product* p2 = new Product("Smartphone", "Electronics", 20000);
    Product* p3 = new Product("Jeans", "Clothing", 1000);
    Product* p4 = new Product("Headphone", "Electronics", 2000);

    Cart* cart = new Cart();
    cart->add_product(p1, 1);
    cart->add_product(p2, 1);
    cart->add_product(p3, 2);
    cart->add_product(p4, 1);
    cart->set_loyalty_member(true);
    cart->set_payment_bank("HDFC");

    cout<<"Original Cart Total: "<<cart->get_initial_total()<<" Rs."<<endl;

    vector<string> applicable = manager->get_applicable_coupons(cart);
    cout<<"Applicable Coupons: "<<endl;
    for(auto& coupon: applicable){
        cout<<"\t- "<<coupon<<endl;
    }

    double final_total = manager->apply_all(cart);
    cout<<"Final Cart total after discounts: "<<final_total<<" Rs."<<endl;

    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete cart;
}