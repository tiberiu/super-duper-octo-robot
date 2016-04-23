#ifndef _GAMECONTEXT_H
#define _GAMECONTEXT_H

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "gameobject.h"
#include "scene.h"

class GameContext {
private:
    GLFWwindow* window;
    std::vector<Scene*> scenes;
    Scene* activeScene;
public:

    void Init();
    void StartEngine();
    void Update();
    void AddScene(Scene* scene);
    void LoadScene(std::string sceneName);
};

#endif
