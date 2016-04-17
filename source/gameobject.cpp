#include "source/gameobject.h"
#include <iostream>

void GameObject::AddComponent(Component* component) {
    this->components.push_back(component);
}

void GameObject::Update() {
    for (int i = 0; i < components.size(); i++) {
        components[i]->Update();
    }
}
