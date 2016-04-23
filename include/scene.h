#ifndef __SCENE_H
#define __SCENE_H

#include <vector>

#include "gameobject.h"

class Scene {
private:
    std::vector<GameObject*> gameObjects;
    bool loaded;

public:
    std::string name;
    std::string dataPath;
 
    Scene(std::string name, std::string dataPath);
    void AddGameObject(GameObject* gameObject);
    void Update();
    void LoadScene();
    void UnloadScene();
};

#endif
