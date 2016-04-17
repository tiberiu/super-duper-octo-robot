#ifndef _COMPONENT_H
#define _COMPONENT_H

class Component {
private:
    bool isActive;
public:
    Component();
    ~Component();

    virtual void Start() {};
    virtual void Update() {};
};

#endif
