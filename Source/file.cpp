#include "file.h"

std::string getFilePath(const std::string& name, const RESOURCE_PATH& path)
{
	//char* used to allow deallocation of memory as SDL_GetBasePath()
	//returns dynamic pointer.
	char* cPath = SDL_GetBasePath();
	std::string basePath = cPath;

	SDL_free(cPath);

	basePath += "Resources/";
	switch (path)
	{
	case AUDIO:
		basePath += "Audio/";
		basePath += name;
		break;
	case GRAPHICS:
		basePath += "Graphics/";
		basePath += name;
	default:
		break;
	}
	return basePath;
}