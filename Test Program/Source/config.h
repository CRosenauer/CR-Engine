/*
	config.cpp

	This file contains preprocesor definitions used to active/deactivate/
	set constant flags and values.


*/

/* General Definitions */
#define TITLE "Pacman"

/*  Video Flags	 */

//resolution which the game will render in
#define RENDERING_SCREEN_WIDTH  224
#define RENDERING_SCREEN_HEIGHT 288

//resolution which the game will be displayed in by default
//rendering resolution will be stretched or scaled to fit or stretch this resolution
#define DEFAULT_DISPLAY_WIDTH   640
#define DEFAULT_DISPLAY_HEIGHT  480
#define DEFAULT_SCALE_MODE      CRE_SCALE_TO_FIT
#define DEFAULT_FULLSCREEN_MODE CRE_DISPLAY_WINDOWED

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

//flag for functions to obtain framerates (currently unimplemented)
#define FRAMERATE_COUNTER

//flags to enable texture rotating and stretching respectively
#define TEXTURE_ROTATING
#define TEXTURE_STRETCHING

//flags to render only textures which would appear on screen (currently unimplemented)
//#define ONSCREEN_RENDER_ONLY


/*  Audio Flags  */
//none so far

/*  Input Flags  */

//const int to determine how many inputs are read
//note: x and y inputs on d-pads or control sticks are counted as 1 input
//ex. for implementing WASD movement you would only need 2 width, one for WS one for AD.
#define INPUTWIDTH 3

//flag for if usb controllers are ready by the input system
//#define CONTROLLER_SUPPORT


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