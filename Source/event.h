#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL_events.h>
#include <queue>
#include <vector>

#include "config.h"

#include "video.h"
#include "audio.h"
#include "entity.h"
#include "entityHandler.h"

//CRE Events are altered versions of SDL's internal event strucuts.
//This change was made to have an easier to use type of event thats still compatible with
//SDL Events.
//CRE Events were made so I didn't need to deal with void pointers in SDL_UserEvents
//and I feel that giving events access to all entities is a cleaner way to update a game
//compared to having a virtual update function in a child class of entity.

//struct to hold CRE event data.
//Note that this is basically a rip off of SDL_UserEvent without information that
//goes unused is not included.

/*
	Event structure based on event codes:

	CRE_EVENT_QUIT:
	generic1-4: unused
	entityID:   unused

		quits the program


	CRE_EVENT_LOAD_SFX
	generic1:   char pointer of the name of the sound file to play.
	generic2-4: unused
	entityID:   unused

		loads .wav file as a sound effect.


	CRE_EVENT_LOAD_MUSIC
	generic1:   char pointer of the name of the music file to play.
	generic2-4: unused.
	entityID:   unused.

		loads .mp3 file as game music


	CRE_EVENT_LOAD_TEXTURE
	generic1:   pointer to the textureData struct to load.
	generic2-4: unused
	entityID:   ID of the entity that the texture will be loaded to.

		loads texture to an entity.


	CRE_EVENT_LOAD_ANIMATION
	generic1:   pointer to the animation struct to load.
	generic2-4: unused
	entityID:   ID of the entity that the animation will be loaded to.

		loads animation to an entity.


	CRE_EVENT_LOAD_GROUNDS
	generic1:   pointer to the groundData struct to load. Calls loadGrounds().
	generic2-4: unused
	entityID:   unused

		loads groundData struct to current background/foregrounds


	CRE_EVENT_SET_GROUNDS
	generic1:   pointer to the groundData struct to set. Calls setGrounds().
	generic2-4: unused
	entityID:   unused

		resets all backgrounds/foregrounds and loads groundData struct to current background/foregrounds


	CRE_EVENT_RESET_GROUNDS
	generic1:   RENDERINGFLAG specifying which type of grounds to remove.
	generic2-4: unused
	entityID:   unused

		removes all backgrounds/foregrounds of type passed RENDERINGFLAG


	CRE_EVENT_ALL_RESET_GROUNDS
	generic1-4: unused
	entityID:   unused

		resets all backgrounds/foregrounds


	CRE_EVENT_LOAD_SCRIPT
	generic1:   pointer to a script struct to load.
	generic2-4: unused
	entityID:   ID of the entity which the script will be applied to. (if applicible)

		loads the script pointed to be generic1.


	CRE_EVENT_FUNCTION
	generic1:   function pointer to the function to operate. (with arguements (entity*, void*)).
	generic2:   void* to the second arguement of the function (if needed)
	generic3-4: unused
	entityID:   reference ID to the entity which the function will be taking effect on (if needed).

		performs a function on an entity (or other specified piece of data).


	CRE_EVENT_GOTO
	generic1:   function that returns the address of the script which this event will jump to.
	generic2:   not defined by user
	generic3-4: unused
	entityID:   not defined by user

		Replaces the script which queued this event with the sciprt returned by function in generic1


	CRE_EVENT_IF_GOTO
	generic1: boolean returning function which takes arguements (entity*, void*).
	generic2: void* arguement to the boolean fucntion
	generic3: function that returns the address of the script which this event will jump to.
	generic4: not defined by user
	entityID: not defined by user

		Used to perfrom some degree of logic with scripts.
		If the boolean function in generic1 returns true replaces script which queued this event
		with the returned by the function in generic3.
		Note: generic3 is a function rather than an address to prevent circular variable dependancies
	
	CRE_EVENT_SPAWN_ENTITY_SCRIPT - currently unimplemented
	generic1-4: pointer to the script(s) that will be loaded to the new entity
	entityID:   unused

		Used to spawn an entity and imediately apply a script(s) to it.
		Scripts in generic1-4 will be applied in order. To terminate the active scripts set any generic
		to NULL.

		ex.) generic 1: pointer to a script
		     generic 2: NULL
		     generic 3: pointer to a script
			 generic 4: pointer to a script

		In this case, when the event handler attempts to push generic 2 to the script handler the event handler
		will see that generic 2 is NULL and will assume that there are no more scripts to load. As such, only
		the script in generic 1 will be loaded to the newly spawned entity.
*/

union CRE_GenericData
{
	void* pointer;
	void* (*function)( CRE_Entity*, void* );
	int data;
};

//event codes used for testing.
//should be located in the "eventType" member of CRE_Event
enum CRE_EventCode
{
#ifdef EVENT_QUIT
	CRE_EVENT_QUIT,
#endif


	//audio events

#ifdef EVENT_LOAD_SFX
	CRE_EVENT_LOAD_SFX,
#endif

#ifdef EVENT_LOAD_MUSIC
	CRE_EVENT_LOAD_MUSIC,
#endif


	//entity graphics events

#ifdef EVENT_LOAD_TEXTURE
	CRE_EVENT_LOAD_TEXTURE,
#endif

#ifdef EVENT_LOAD_ANIMATION
	CRE_EVENT_LOAD_ANIMATION,
#endif


	//grounds events

#ifdef EVENT_LOAD_GROUNDS
	CRE_EVENT_LOAD_GROUNDS,
#endif

#ifdef EVENT_SET_GROUNDS
	CRE_EVENT_SET_GROUNDS,
#endif

#ifdef EVENT_RESET_GROUNDS
	CRE_EVENT_RESET_GROUNDS,
#endif

#ifdef EVENT_RESET_GROUNDS
	CRE_EVENT_RESET_ALL_GROUNDS,
#endif


	//entity based events

#ifdef EVENT_SPAWN_ENTITY_SCRIPT
	CRE_EVENT_SPAWN_ENTITY_SCRIPT
#endif // EVENT_SPAWN_ENTITY_SCRIPT


	//operation events

#ifdef EVENT_LOAD_SCRIPT
	CRE_EVENT_LOAD_SCRIPT,
#endif

#ifdef EVENT_FUNCTION
	CRE_EVENT_FUNCTION,
#endif

#ifdef EVENT_GOTO
	CRE_EVENT_GOTO,
#endif

	//logical events

#ifdef EVENT_IF_GOTO
	CRE_EVENT_IF_GOTO,
#endif
};

struct CRE_Event
{
	//piece of data telling the engine what do to with this information
	CRE_EventCode eventType = CRE_EVENT_QUIT;

	//generic unions to store data, function, and addresses
	CRE_GenericData generic1 = { NULL };
	CRE_GenericData generic2 = { NULL };
	CRE_GenericData generic3 = { NULL };
	CRE_GenericData generic4 = { NULL };

	//reference entity ID.
	unsigned int entityID = 0;
};

//returns string version of the passed event code
//basically what you see in enum CRE_EVENT_CODE
string eventCodeToString(const CRE_EventCode& code);

#endif //EVENT_HPP