#ifndef CRENGINE_H
#define CRENGINE_H

#include <cstdio>
#include <new>
#include <vector>

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

//file which contains game logic function goes here.
#include "source/g_Pacman.h"

#include "entity.h"
#include "input.h"
#include "video.h"
#include "audio.h"
#include "scriptHandler.h"
#include "eventHandler.h"
#include "timer.h"


//initialized anything that needs to be set up in CR Engine
//first initialized memory
//then creates handling objects
//then setups SDL
void CREInit();

//initializes CREInit then enters CRELoop game loop
//after exiting CRELoop cleans up memory used
//then exits CREMain returning to the standard int main
//Note: Should be the only thing in int main aside from return 0;
void CREMain();

//game loop that will constantly be repeated
//loop exits when exit event is pushed.
void CRELoop();

//cleans up memory allocated to heap and finishes up anything else
//that needs to be finished before exiting the program.
void CRECleanup();

#endif //CRENGINE_H