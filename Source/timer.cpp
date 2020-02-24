#include "timer.h"

static Uint32 ticks;

//default to 17 ms per frame or about 60fps
static unsigned int msPerFrame = 17;

void setFrameTimer()
{
	ticks = SDL_GetTicks();
}

void pollFrameTimer()
{
	while (true)
	{
		if (SDL_GetTicks() - ticks >= msPerFrame)
			break;
	}
}

void setFrameRate(const unsigned int& frameRate)
{
	msPerFrame = (unsigned int) (float) 1000 / (float) frameRate;
	printf("msPerFrame: %i\n", msPerFrame);
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