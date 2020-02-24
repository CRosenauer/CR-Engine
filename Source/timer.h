#ifndef TIMER_H
#define TIMER_H

#include <cstdio>

#include <SDL_timer.h>

void setFrameTimer();
//polls time before the program has started in ms.
//stores that value in internal memory.

void pollFrameTimer();
//will ensure the program doesnt continue until 17ms has
//passed before program resumes

void setFrameRate(const unsigned int& frameRate);
//sets max framerate to inputted variable.

void pollMSTimer();

Uint32 getMSTimer();

#endif //TIMER_H