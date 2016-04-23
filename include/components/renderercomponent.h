#ifndef _RENDERER_H
#define _RENDERER_H

#include "components/component.h"
#include "geometry/mesh.h"

// EngineComponent(RendererComponent)
class RendererComponent : public Component {
public:
    // EngineComponentField(Mesh, mesh)
    Mesh* mesh;

    void Update();
};

#endif
