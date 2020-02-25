/*
	config.cpp

	This file contains preprocesor definitions used to active/deactivate/
	set constant flags and values.


*/

/*  Video Flags	 */

//resolution which the game will render in
#define RENDERING_SCREEN_WIDTH  640
#define RENDERING_SCREEN_HEIGHT 480

//resolution which the game will be displayed in by default
//rendering resolution will be stretched or scaled to fit or stretch this resolution
#define DEFAULT_DISPLAY_WIDTH   640
#define DEFAULT_DISPLAY_HEIGHT  480

//flag to determine if the game will be displayed in windowed, fullscreen, or
//boarderless fullscreen
//	****WARNING: DO NOT HAVE SEVERAL FLAGS ACTIVE AT THE SAME TIME
#define DEFAULT_DISPLAY_TYPE_WINDOWED
//#define DEFAULT_DISPLAY_TYPE_FULLSCREEN
//#define DEFAULT_DISPLAY_TYPE_BOARDERLESS

//default frame rate of the game engine (tied to length of game cycle)
#define DEAFULT_FRAME_RATE 60

//flag if the game's framerate will be locked
#define FRAMECAP

//flag for functions to obtain framerates
#define FRAMECOUNTER

//flags to determine how the engine will fit the internal rendering resolution to
//the display resolution
//	****WARNING: DO HAVE BOTH FLAGS ACTIVE AT THE SAME TIME!
#define STRETCH_TO_FIT
//#define SCALE_TO_FIT

//flags to enable texture rotating and stretching respectively
#define TEXTURE_ROTATING
#define TEXTURE_STRETCHING

//flags to render only textures which would appear on screen
#define ONSCREEN_RENDER_ONLY


/*  Audio Flags  */


/*  Input Flags  */

//flag for if usb controllers are ready by the input system
#define CONTROLLER_SUPPORT


/*  Event Flags  */

//Event type preproccessor
#define EVENT_QUIT

//audio events
#define EVENT_LOAD_SFX
#define EVENT_LOAD_MUSIC
//#define FORCE_STOP_MUSIC

//video events
//none so far

//entity graphics events
#define EVENT_LOAD_TEXTURE
#define EVENT_LOAD_ANIMATION

//grounds events
#define EVENT_LOAD_GROUNDS
#define EVENT_SET_GROUNDS
#define EVENT_RESET_GROUNDS

//operation script events
#define EVENT_LOAD_SCRIPT
#define EVENT_FUNCTION
#define EVENT_GOTO

//logical script events
#define EVENT_IF_GOTO