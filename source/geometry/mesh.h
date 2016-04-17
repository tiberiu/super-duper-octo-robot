#ifndef _MESH_H
#define _MESH_H

#include <vector>
#include "source/geometry/Vector3.h"

class Mesh {
public:
    std::vector<Vector3*> vertices;
    std::vector<int> triangles;
};

#endif
