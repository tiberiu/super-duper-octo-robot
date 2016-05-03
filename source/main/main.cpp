#include <iostream>
#include <typeinfo>
#include <vector>
#include <string>

#include "components/transformcomponent.h"
#include "components/renderercomponent.h"
#include "geometry/vector3.h"

using namespace std;

int main() {
    RendererComponent* renderer = new RendererComponent();
    TransformComponent* transform = new TransformComponent();
    transform->position = new Vector3(1, 1, 1);
    transform->rotation = new Vector3(2, 2, 2);
    transform->scale = new Vector3(3, 3, 3);

    Vector3* TransformComponent::*positionPtr = &TransformComponent::position;
    Vector3* TransformComponent::*rotationPtr = &TransformComponent::rotation;
    Vector3* TransformComponent::*scalePtr = &TransformComponent::scale;
    std::string (Vector3::*toStringPointer)() = NULL;
    toStringPointer = &Vector3::toString;

    vector<Vector3* TransformComponent::*> v;
    v.push_back(positionPtr);
    v.push_back(rotationPtr);
    v.push_back(scalePtr);

    for (int i = 0; i < v.size(); i++) {
        cout << ((transform->*v[i])->*toStringPointer)() << endl;
    }
}
