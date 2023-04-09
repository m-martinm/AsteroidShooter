#pragma once
#include "Observer.h"
#include <vector>
class Signal
{
private:
    std::vector<Observer*> observers;
public:
    virtual ~Signal() {}

    void registerObserver(Observer* observer);
    void unregisterObserver(Observer* observer);
    void notifyObservers();
};

