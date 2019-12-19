#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>

#include <string>
#include <queue>

#include "file.h"

enum CRE_AUDIO_FLAG
{

};

class audio
{
public:
	audio();

	void loadSFX(const std::string& path);
	//loads and queues a sound file from path to be played.
	//accepts file types: WAVE, AIFF, RIFF, OGG, and VOC.
	//Note: By default only wave in initialized. Change in CREngine.cpp, init()

	void loadMusic(const std::string& path);
	//loads music track to be played.
	//accepts file types: WAVE, MOD, MIDI, OGG, MP3, and FLAC.
	//Note: By default only mp3 in initialized. Change in CREngine.cpp, init()

	//implement music fadding flags
	void playAudio();
	//plays queued sounds, and if no b.g. music is playing, plays current queued music.

	//implement music fadding flags
	void forceMusic();
	//forces currently loaded music to play.

	Mix_Music* getMusic();

private:
	Mix_Music* music;

	std::queue<Mix_Chunk*> audioQueue;
};

#endif //AUDIO_H