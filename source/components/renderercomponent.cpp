#include "components/component.h"
#include "components/renderercomponent.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <iomanip>

void RendererComponent::Update() {
    for (int i = 0; i < mesh->triangles.size(); i += 3) {
        glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
 
        for (int j = i; j < i + 3; j++) {
            int idx = mesh->triangles[j];
            Vector3* vertex = mesh->vertices[idx];
            glVertex3f(vertex->x, vertex->y, vertex->z);
        }

        glEnd();
    }
}
