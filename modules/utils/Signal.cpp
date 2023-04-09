#include "Signal.h"
#include <iostream>
void Signal::registerObserver(Observer* observer)
{
	observers.push_back(observer);
}
void Signal::unregisterObserver(Observer* observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        observers.erase(it);
    }
}
void Signal::notifyObservers()
{

    for (Observer* observer : observers) {
        observer->update();
    }
}