#ifndef _GAMECONTEXT_H
#define _GAMECONTEXT_H

#include <vector>
#include <string>
#include <GLFW/glfw3.h>

#include "source/gameobject.h"
#include "source/scene.h"

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
