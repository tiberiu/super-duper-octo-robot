#include "source/scene.h"
#include "source/serializer/serializer.h"

Scene::Scene(std::string name, std::string dataPath) {
    this->name = name;
    this->dataPath = dataPath;
}

void Scene::Update() {
    if (!this->loaded) {
        return;
    }

    for (int i = 0; i < gameObjects.size(); i++) {
        gameObjects[i]->Update();
    }
}

void Scene::AddGameObject(GameObject* gameObject) {
    gameObjects.push_back(gameObject);
}

void Scene::LoadScene() {    
    this->loaded = true;

    cout << "LOADING SCENE" << endl;
    Serializer serializer = Serializer();
    string raw_data = serializer.LoadRawData(this->dataPath);
    cout << "LOADED SCENE RAW DATA" << endl;
    serializer.LoadScene(raw_data, *this);
    cout << "DONE" << endl;
}

 void Scene::UnloadScene() {
     // TODO: Nothing for now
     this->loaded = false;
 }
