#ifndef TESTGAME_H
#define TESTGAME_H

#include <SDL_events.h>

#include <vector>

#include "audio.h"
#include "video.h"
#include "entity.h"
#include "testAnim.hpp"
#include "script.h"
#include "testScript.hpp"


//logic for the game
//reads the inputs and updates game accordingly before playing audio and rendering graphics.
void TestGame();

#endif //TESTGAME_H