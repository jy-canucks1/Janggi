#ifndef __SUBJECT_H__
#define __SUBJECT_H__
#include "observer.h"
#include <vector>
#include <memory>

class Subject {
protected:
    std::vector<std::shared_ptr<Observer>> observers;
public:
    Subject() = default;
    void attach(std::shared_ptr<Observer> o);
    void detach(std::shared_ptr<Observer> o);
    virtual void notify() = 0;
    virtual ~Subject() = default;
};


#endif
