#ifndef _RENDERER_H
#define _RENDERER_H

#include "source/geometry/mesh.h"

// EngineComponent(RendererComponent)
class RendererComponent : public Component {
public:
    // EngineComponentField(Mesh, mesh)
    Mesh* mesh;

    void Update();
};

#endif
