#include <iostream>
#include <fstream>

#include "gamecontext.h"
#include "scene.h"
#include "serializer/serializer.h"
#include "serializer/encoder.h"

using namespace std;

int main() {
    Serializer serializer;
    string rawGameData = serializer.LoadRawData("resources/test_data/test_game_data.in");
    vector<Scene*> scenes = serializer.LoadGameData(rawGameData);

    GameContext* gameContext = new GameContext();
    gameContext->Init();

    for (int i = 0; i < scenes.size(); i++) {
        gameContext->AddScene(scenes[i]);
    }

    gameContext->LoadScene(scenes[1]->name);
    gameContext->StartEngine(); 

    return 0;
}
