#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include "geometry/Vector3.h"

// EngineObject(Mesh)
class Mesh {
public:
    // EngineField(array<Vector3>, vertices)
    std::vector<Vector3*> vertices;
    // EngineField(array<int>, triangles)
    std::vector<int> triangles;
};

#endif
