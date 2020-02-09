#ifndef TESTGAME_H
#define TESTGAME_H

#include <SDL_events.h>

#include "audio.h"
#include "video.h"
#include "input.h"
#include "entity.h"
#include "script.h"
#include "ground.h"

#include "testGrounds.hpp"
#include "testTexture.hpp"
#include "testAnim.hpp"
#include "testScript.hpp"


void TestGame();
//logic for the game
//reads the inputs and updates game accordingly.

#endif //TESTGAME_H