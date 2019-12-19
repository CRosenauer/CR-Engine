#include "file.h"

std::string getFilePath(const std::string& name, const RESOURCE_PATH& path)
{
	std::string basePath = SDL_GetBasePath();
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