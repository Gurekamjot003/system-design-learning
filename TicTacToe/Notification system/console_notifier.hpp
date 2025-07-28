#pragma once
#include "iobserver.hpp"

class ConsoleNotifier : public IObserver {
public:
    void update(string msg) override {
        cout << "Notification: " << msg << endl;
    }
};