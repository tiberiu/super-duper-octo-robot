#ifndef _RENDERER_H
#define _RENDERER_H

#include "source/geometry/mesh.h"

// EngineComponent(RendererComponent)
class RendererComponent : public Component {
public:
    Mesh* mesh;

    void Update();
};

#endif
