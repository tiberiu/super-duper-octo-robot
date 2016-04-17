#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include <vector>
#include <string>

#include "source/components/component.h"

class GameObject {
public:
    std::string name;
    std::vector<Component*> components;

    GameObject(std::string _name) : name(_name) {};
    ~GameObject() {};
    void Update();
    void AddComponent(Component* component);
};

#endif
