#include "CREngine.h"

const std::string TITLE = "Test Game";
//as the title suggests, game title.

int screenWidth = 640;
int screenHeight = 480;
//screen resolution
//should be able to be changed in the menu

Uint32 windowFlag = SDL_WINDOW_SHOWN;
//window flag, used to determine fullscreen etc.
//should be able to be changed in the menu

SDL_Renderer *CRERenderer = NULL;
//main renderer for drawing to screen

extern vector<entity*> entityBlock;

//Handlers for input, video, etc.
inputHandler  CREInput;
video         CREVideo;
audio         CREAudio;
scriptHandler CREScriptHandler;
eventHandler  CREEventHandler;


void CREInit()
{
	/*** Engine Component Initialization Block ***/

	//video window associated with current title, screen size, widescreen support, etc.
	CREVideo = video(TITLE, screenWidth, screenHeight, windowFlag);

	const int IMG_FLAGS = IMG_INIT_PNG;

	//initialize IMG and Audio.
	if (!(IMG_Init(IMG_FLAGS) & IMG_FLAGS))
	{
		printf("CREngine init error. Failed to initialized SDL_Image.\nSDL Error: %s", IMG_GetError());
		exit(1);
	}

	const int AUDIO_FLAGS = MIX_INIT_MP3;

	if ((Mix_Init(AUDIO_FLAGS) & AUDIO_FLAGS) != AUDIO_FLAGS)
	{
		printf("CREngine init erorr Failed to initalize SDL_Mixer.\nSDL Error: %s", Mix_GetError());
		exit(1);
	}

	const int SDL_FLAGS =
		SDL_INIT_VIDEO |
		SDL_INIT_AUDIO |
		SDL_INIT_TIMER |
#ifdef CONTROLLER_SUPPORT
		SDL_INIT_GAMECONTROLLER |
#endif
		0; //terminator for bitwise operator that doesn't change anything

	//initialize SDL
	if (SDL_Init(SDL_FLAGS) != 0)
	{
		printf("CREngine init error. Failed to initialize SDL.\nSDL Error: %s", SDL_GetError());
		exit(1);
		//exits program on failure to initialize SDL.
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		printf("CREngine init error. Failed to open SDL_Mixer channels.\nSDL Error: %s", Mix_GetError());
		exit(1);
	}

	Mix_AllocateChannels(8);

	Mix_VolumeMusic(MIX_MAX_VOLUME/4);

	CREVideo.init();
	
	//initalizes game logic to read and write inputs, entities, audio, video, etc.

	pollFrameTimer();
}

void CREMain()
{
	CREInit();
	//initialized memory and internal objects.

	CRELoop();
	//internal game loop
	//will loop until exit event occurs.

	CRECleanup();
	//cleans up memory before exiting program.
}

void CRELoop()
{
	while( true )
	{
		//read inputs
		CREInput.pollInputs();
		
		//game logic function
		TestGame();

		//process currently loaded scripts
		CREScriptHandler.processScripts();

		//updates game based on queued events
		if (!CREEventHandler.processEvents())
			break;

		//play user feedback
		CREAudio.playAudio();

		//draw queues textures to be rendered and draws images to the screen
		CREVideo.render();
	}
}

void CRECleanup()
{
	//deallocate entity*s from entityBlock
	for (unsigned int i = 0; i < entityBlock.size(); i++)
	{
		delete entityBlock[i];
	}

	//clean up entityBlock's entity**
	entityBlock.clear();

	//clean up backgrounds and foregrounds
	resetGround();

	//clean events
	//clean scripts

	//shut down graphics, audio, and SDL subsystems.
	IMG_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}