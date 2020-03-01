#include "CREngine.h"

//main renderer for drawing images
SDL_Renderer* CREInternalRenderer = NULL;

int screenWidth = 640;
int screenHeight = 480;
//screen resolution
//should be able to be changed in the menu

Uint32 windowFlag = SDL_WINDOW_SHOWN;
//window flag, used to determine fullscreen etc.
//should be able to be changed in the menu

extern vector<CRE_Entity*> entityBlock;

//Handlers for input, video, etc.
CRE_InputHandler  CREInput;
CRE_Video         CREVideo;
CRE_Audio         CREAudio;
CRE_ScriptHandler CREScriptHandler;
CRE_EventHandler  CREEventHandler;


void CREInit()
{
	/*** Engine Component Initialization Block ***/

	//video window associated with current title, screen size, widescreen support, etc.
	CREVideo = CRE_Video(screenWidth, screenHeight, windowFlag);

	const int IMG_FLAGS = IMG_INIT_PNG;

	//initialize IMG and Audio.
	if (!(IMG_Init(IMG_FLAGS) & IMG_FLAGS))
	{
		printf("CREngine init error. Failed to initialize SDL_Image.\nSDL Error: %s\n", IMG_GetError());
		//exit(1);
	}

	const int AUDIO_FLAGS = MIX_INIT_MP3;

	if ((Mix_Init(AUDIO_FLAGS) & AUDIO_FLAGS) != AUDIO_FLAGS)
	{
		printf("CREngine init erorr Failed to initalize SDL_Mixer.\nSDL Error: %s\n", Mix_GetError());
		//exit(1);
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

#ifdef PRINT_FRAMECOUNT
namespace
{
	static unsigned frameCount = 0;
}
#endif

void CRELoop()
{
	while( true )
	{
#ifdef PRINT_FRAMECOUNT
		printf("Frame: %i\n", frameCount++);
#endif // PRINT_FRAMECOUNT

#ifdef COMPONENT_MS_TIMER
		pollMSTimer();
#endif COMPONENT_MS_TIMER
		//read inputs
		CREInput.pollInputs();

#ifdef COMPONENT_MS_TIMER
		printf("Input runtime: %i\n", getMSTimer());
		
		pollMSTimer();
#endif COMPONENT_MS_TIMER
		
		//game logic function
		TestGame();

#ifdef COMPONENT_MS_TIMER
		printf("Game logic runtime: %i\n", getMSTimer());
		
		pollMSTimer();
#endif COMPONENT_MS_TIMER

		//process currently loaded scripts
		CREScriptHandler.processScripts();

#ifdef COMPONENT_MS_TIMER
		printf("Script handler runtime: %i\n", getMSTimer());
		
		pollMSTimer();
#endif COMPONENT_MS_TIMER

		//updates game based on queued events
		if (!CREEventHandler.processEvents())
			break;

#ifdef COMPONENT_MS_TIMER
		printf("Event handler runtime: %i\n", getMSTimer());
		
		pollMSTimer();
#endif COMPONENT_MS_TIMER

		//play user feedback
		CREAudio.playAudio();

#ifdef COMPONENT_MS_TIMER
		printf("Audio runtime: %i\n", getMSTimer());
		
		pollMSTimer();
#endif COMPONENT_MS_TIMER

		//draw queues textures to be rendered and draws images to the screen
		CREVideo.render();

#ifdef COMPONENT_MS_TIMER
		printf("Video runtime: %i\n\n", getMSTimer());
#endif COMPONENT_MS_TIMER

#ifdef MANUAL_ADVANCE_FRAME
		system("PAUSE");
#endif MANUAL_ADVANCE_FRAME
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