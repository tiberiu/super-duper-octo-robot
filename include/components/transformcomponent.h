#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "components/component.h"
#include "geometry/vector3.h"

// EngineComponent(TransformComponent)
class TransformComponent : public Component {
public:
    // EngineField(Vector3, position)
    Vector3* position;
    // EngineField(Vector3, rotation)
    Vector3* rotation;
    // EngineField(Vector3, scale)
    Vector3* scale;
};

#endif
