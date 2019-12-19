#ifndef FILE_H
#define FILE_H

#include <string>
#include <SDL_filesystem.h>

enum RESOURCE_PATH
{
	GRAPHICS,
	AUDIO
};

std::string getFilePath(const std::string& name, const RESOURCE_PATH& path);
//returns the path of the passed image or sound file, etc
//returned path is based on if the RESOURCE_PATH is requiresting audio or image file.

#endif //FILE_H