#include "timer.h"

static Uint32 ticks;
static unsigned int msPerFrame;

void setFrameTimer()
{
	ticks = SDL_GetTicks();
}

void pollFrameTimer()
{
	while (true)
	{
		Uint32 currentTicks = SDL_GetTicks();

		if (currentTicks - ticks >= msPerFrame)
			break;
	}
}

void setFrameRate(const unsigned int& frameRate)
{
	msPerFrame = 1000 / frameRate;
}