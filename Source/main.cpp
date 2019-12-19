#include "CREngine.h"
#include <SDL_filesystem.h>

int main(int argc, char* argv[])
{

	printf(SDL_GetBasePath());

	CREMain();

	return 0;
}