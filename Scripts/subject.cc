#include "subject.h"

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::detach(std::shared_ptr<Observer> o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
}
