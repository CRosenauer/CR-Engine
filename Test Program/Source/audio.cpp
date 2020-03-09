#include "audio.h"

CRE_Audio::CRE_Audio()
{
	music = NULL;
}

void CRE_Audio::loadSFX(const std::string& path)
{
	std::string tempString = getFilePath(path, AUDIO);
	Mix_Chunk* audio = Mix_LoadWAV(tempString.c_str());
	//Load sound file from ROM to memory.

	if (audio == NULL)
	{
		printf("CREngine Audio Warning. Sound file \"%s\" could not be loaded.\nMixer error: %s\n", tempString.c_str(), Mix_GetError());
	}
	else
	{
		audioQueue.push(audio);
		//push sound file to audio playing queue.
	}

	
}

void CRE_Audio::playAudio()
{
	//loads sounds from audio queue to play.
	while (!audioQueue.empty())
	{
		Mix_Chunk*  tempAudio = audioQueue.front();
		Mix_PlayChannel(-1, tempAudio, 0);
		audioQueue.pop();
	}

	//plays background music if none is playing currently.
	//broken piece of code?
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(music, 0);
	}
}

void CRE_Audio::loadMusic(const std::string& path)
{
	std::string tempString = getFilePath(path, AUDIO);
	music = Mix_LoadMUS(tempString.c_str());

	if (music == NULL)
	{
		printf("Can't load music from %s.\nSDL_Mixer Error: %s\n", tempString.c_str(), Mix_GetError());
	}
}

Mix_Music* CRE_Audio::getMusic()
{
	return music;
}