#ifndef __OBSERVER_H__
#define __OBSERVER_H__

class Vertex;

class Observer {
public:
    virtual void update(Vertex &vertex) = 0;
    virtual ~Observer() = default;
};

#endif
