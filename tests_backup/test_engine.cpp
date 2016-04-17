#include <stdlib.h>
#include <stdio.h>

#include "../source/gamecontext.h"

int main() {
    GameContext* gameContext = new GameContext();
    gameContext->Init();
    gameContext->StartEngine();
}
