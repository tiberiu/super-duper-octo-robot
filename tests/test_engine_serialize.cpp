#include <iostream>
#include <fstream>

#include "source/gamecontext.h"
#include "source/scene.h"
#include "source/serializer/serializer.h"
#include "source/serializer/encoder.h"

using namespace std;

int main() {
    Serializer serializer;
    string rawGameData = serializer.LoadRawData("tests/test_data/test_game_data.in");
    vector<Scene*> scenes = serializer.LoadGameData(rawGameData);

    GameContext* gameContext = new GameContext();
    gameContext->Init();
 
    for (int i = 0; i < scenes.size(); i++) {
        cout << scenes[i]->name << " " << scenes[i]->dataPath << endl;
        gameContext->AddScene(scenes[i]);
    }

    cout << "LOAD SCENE " << scenes[1]->name << endl;
    gameContext->LoadScene(scenes[1]->name);
    gameContext->StartEngine(); 

    return 0;
}
