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

SDL_Renderer* CRERenderer = NULL;
//main renderer for drawing to screen

//Buses to hold user inputs, and entities respectively
__int8* inputBus = NULL;
entity* entityBlock = NULL;

//Handlers for input and video.
inputHandler CREinput;
video        CREVideo;
audio        CREAudio;

const int INPUTWIDTH = 3;

void CREInit()
{
	/*** Memory Allocation Block ***/
	//allocate inputBus
	try
	{
		printf("Stub: Initializing 3 inputs on inputBus");
		inputBus = new __int8[INPUTWIDTH];
	}
	catch (std::bad_alloc)
	{
		printf("CREngine init error. Failed to initialize inputBus. Exiting program\n");
		exit(1);
	}

	//allocate enetiyBlock
	try
	{
		printf("Stub: Initializing 64 entities on entityBlock.\n");
		entityBlock = new entity[64];
		//allocates memory on the heap to entities
		//in the future will be loaded based on memory allocation on ini files.
	}
	catch (std::bad_alloc)
	{
		printf("CREngine init error. Failed to initialize entityBlock. Exiting program\n");
		exit(1);
		//error handling for memory allocation
		//if memory cannot be initialized then program exits.
	}

	//establish entity textures with renderering system
	for (int i = 0; i < 64; i++)
	{
		entityBlock[i] = entity(CRERenderer);
	}

	/*** Engine Component Initialization Block ***/
	printf("Stub: Initializing inputHandler with stub inputBus, 3 inputBusWidth.\n");
	CREinput = inputHandler(3, inputBus);
	//inputHandler associated with inputBus.

	CREVideo = video(TITLE, screenWidth, screenHeight, windowFlag, CRERenderer);
	//video window associated with current title, screen size, widescreen support, etc.

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

	const int SDL_FLAGS = SDL_INIT_VIDEO | SDL_INIT_AUDIO;

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

	gameLogicInit(inputBus, entityBlock, &CREVideo, &CREAudio);

	
	//initalizes game logic to read and write inputs, entities, audio, video, etc.
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
	SDL_Event e;

	do
	{
		//read inputs
		CREinput.pollInputs();

		//game logic function
		TestGame();

		//play user feedback
		CREAudio.playAudio();

		CREVideo.render();

		//poll for quit
		SDL_PollEvent(&e);
	}
	while (e.type != SDL_QUIT);
}

void CRECleanup()
{
	//deallocate inputs entityBlock from heap
	delete[] inputBus;
	delete[] entityBlock;

	//shut down graphics, audio, and SDL subsystems.
	IMG_Quit();
	Mix_CloseAudio();
	SDL_Quit();
}