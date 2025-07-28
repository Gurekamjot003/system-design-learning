#pragma once
#include "iobserver.hpp"

class ConsoleNotifier: public IObserver{
public:
    void update(string& message) override {
        cout << "Notification: " << message << endl;
    }
};