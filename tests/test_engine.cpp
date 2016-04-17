#include <iostream> 
#include <stdlib.h>

#include "source/gamecontext.h"
#include "source/gameobject.h"

#include "source/components/transformcomponent.h"
#include "source/components/renderercomponent.h"
#include "source/geometry/mesh.h"
#include "source/geometry/vector3.h"

int main() {
    Scene* scene1 = new Scene("MainScene", "main_scene.sc");

    GameContext* gameContext = new GameContext();
    gameContext->Init();
   
    GameObject* go1 = new GameObject("go1");
    scene1->AddGameObject(go1);

    TransformComponent* transform = new TransformComponent(); 
    transform->position = new Vector3(0, 0, 0);
    transform->rotation = new Vector3(0, 0, 0);
    transform->scale = new Vector3(1, 1, 1);

    go1->AddComponent(transform);

    RendererComponent* renderer = new RendererComponent();
    Mesh* mesh = new Mesh();
    
    std::vector<Vector3*> vertices;
    vertices.push_back(new Vector3(-0.5, -0.2, 0));
    vertices.push_back(new Vector3(0.5, -0.2, 0));
    vertices.push_back(new Vector3(0, 0.5, 0));
 
    mesh->vertices = std::vector<Vector3*>(vertices);

    static const int triangles[] = {0, 1, 2};
    mesh->triangles = std::vector<int>(triangles, triangles + sizeof(triangles) / sizeof(triangles[0]));
    renderer->mesh = mesh;

    go1->AddComponent(renderer);

    std::cout << "Adding scene" << std::endl;
    gameContext->AddScene(scene1);
    std::cout << "Loading scene" << std::endl;
    gameContext->LoadScene(scene1->name);
    std::cout << "Starting Engine" << std::endl;
    gameContext->StartEngine(); 
}
