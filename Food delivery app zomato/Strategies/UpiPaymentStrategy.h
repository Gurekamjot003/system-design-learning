#ifndef UPI_PAYMENT_STRATEGY_H
#define UPI_PAYMENT_STRATEGY_H

#include "../Strategies/PaymentStrategy.h"
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

class UpiPaymentStrategy : public PaymentStrategy {
private:
    string mobile;
public:
    UpiPaymentStrategy(const string& mobile) {
        this->mobile = mobile;
    }

    void pay(double amount) override {
        cout << "Paid " << amount << " using UPI("<<mobile<<")" << endl;
    }

    ~UpiPaymentStrategy() {}
};

#endif