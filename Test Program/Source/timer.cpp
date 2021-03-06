#include "timer.h"

#include <cmath>

#include "config.h"

static Uint32 ticks;

//default to 17 ms per frame or about 60fps
static unsigned int msPerFrame = round( (float) DEAFULT_FRAME_RATE / (float) 1000);

void setFrameTimer()
{
	ticks = SDL_GetTicks();
}

void pollFrameTimer()
{
	//delays the program atleast until msPerFrame milliseconds have passed since setFrameTimer was last called.
	while (true)
	{
		if (SDL_GetTicks() - ticks >= msPerFrame)
			break;
	}
}

void setFrameRate(const unsigned int& frameRate)
{
	msPerFrame = round((float) 1000 / (float) frameRate);
}

static Uint32 msTicks;

void pollMSTimer()
{
	msTicks = SDL_GetTicks();
}

Uint32 getMSTimer()
{
	return SDL_GetTicks() - msTicks;
}