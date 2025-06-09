#ifndef CREDIT_CARD_PAYMENT_STRATEGY_H
#define CREDIT_CARD_PAYMENT_STRATEGY_H

#include "../Strategies/PaymentStrategy.h"
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

class CreditCardPaymentStrategy : public PaymentStrategy {
private:
    string card_number;
public:
    CreditCardPaymentStrategy(const string& card_number) {
        this->card_number = card_number;
    }

    void pay(double amount) override {
        cout << "Paid " << amount << " using CreditCard("<<card_number<<")" << endl;
    }

    ~CreditCardPaymentStrategy() {}
};

#endif