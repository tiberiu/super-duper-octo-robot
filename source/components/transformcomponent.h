#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "source/components/component.h"
#include "source/geometry/vector3.h"

// EngineComponent(TransformComponent)
class TransformComponent : public Component {
public:
    // EngineComponentField(Vector3, position)
    Vector3* position;
    // EngineComponentField(Vector3, rotation)
    Vector3* rotation;
    // EngineComponentField(Vector3, scale)
    Vector3* scale;
};

#endif
