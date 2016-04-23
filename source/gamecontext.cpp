#include <cstdlib>
#include <iostream>

#include "source/gamecontext.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void GameContext::Init() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    window = glfwCreateWindow(640, 480, "Engine Example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, key_callback);
}

void GameContext::StartEngine() {
    while (!glfwWindowShouldClose(window)) {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        this->Update();
 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void GameContext::Update() {   
    if (!this->activeScene) {
        std::cout << "WARNING: No active scene" << std::endl;
        return;       
    }
    
    this->activeScene->Update();
}

void GameContext::AddScene(Scene* scene) {
    this->scenes.push_back(scene);
}

void GameContext::LoadScene(std::string sceneName) {
    if (this->activeScene) {
        this->activeScene->UnloadScene();
        this->activeScene = NULL;
    }

    for (int i = 0; i < this->scenes.size(); i++) {
        if (this->scenes[i]->name == sceneName) {
            this->activeScene = this->scenes[i];
            this->activeScene->LoadScene();
            break;
        }
    }   
}
