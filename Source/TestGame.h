#ifndef TESTGAME_H
#define TESTGAME_H

#include <SDL_events.h>

#include "audio.h"
#include "video.h"
#include "entity.h"



void gameLogicInit(__int8*& inputB, entity*& entityB, video* video, audio* audio);
//initalizes game logic to read and write inputs, entities, audio, video, etc.

void TestGame();
//logic for the game
//reads the inputs and updates game accordingly.

#endif //TESTGAME_H