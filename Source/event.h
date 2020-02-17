#ifndef EVENT_HPP
#define EVENT_HPP

//Event type preproccessor
#define EVENT_QUIT
#define EVENT_LOAD_SFX
#define EVENT_LOAD_MUSIC
#define EVENT_LOAD_TEXTURE
#define EVENT_LOAD_ANIMATION
#define EVENT_LOAD_GROUNDS
#define EVENT_SET_GROUNDS
#define EVENT_RESET_GROUNDS
#define EVENT_LOAD_SCRIPT
#define EVENT_FUNCTION
#define EVENT_IF_GOTO


#include <SDL_events.h>
#include <queue>
#include <vector>

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
	If you are reading this then i forgot to  remove this piece of reference code.
	
	This is somewhat undefined territory but if it work it works i guess.
	
	To me for later reference:
	we can use a union as a piece of undefined data as a pointer to data, a piece of data,
	or as a function pointer.

	Is this good practice? Likely not. Is it functional? Hopefully.

	Also if you read this try not to judge me too hard.

#include <cstdio>

void* test()
{
	printf("Test\n");
	//intentionally doesn't return a value;
}

union test
{
	void* value;
	void* (*function)();
};

int main()
{
	union test asdf = { (void*) 1 };

	printf("%p\n", asdf.value);
	printf("%p\n", asdf.function);

	asdf.function = test;

	asdf.function();
}

*/

union genericData
{
	int data;
	void* pointer;
	void* (*function)( entity*, void* );
};

//event codes used for testing.
//should be located in the "eventType" member of CRE_Event
enum CREEventCode
{
#ifdef EVENT_QUIT
	CRE_EVENT_QUIT,
#endif

#ifdef EVENT_LOAD_SFX
	CRE_EVENT_LOAD_SFX,
#endif

#ifdef EVENT_LOAD_MUSIC
	CRE_EVENT_LOAD_MUSIC,
#endif

#ifdef EVENT_LOAD_TEXTURE
	CRE_EVENT_LOAD_TEXTURE,
#endif

#ifdef EVENT_LOAD_ANIMATION
	CRE_EVENT_LOAD_ANIMATION,
#endif

#ifdef EVENT_LOAD_GROUNDS
	CRE_EVENT_LOAD_GROUNDS,
#endif

#ifdef EVENT_SET_GROUNDS
	CRE_EVENT_SET_GROUNDS,
#endif

#ifdef EVENT_RESET_GROUNDS
	CRE_EVENT_RESET_GROUNDS,
#endif

#ifdef EVENT_LOAD_SCRIPT
	CRE_EVENT_LOAD_SCRIPT,
#endif

#ifdef EVENT_FUNCTION
	CRE_EVENT_FUNCTION,
#endif

#ifdef EVENT_IF_GOTO
	CRE_EVENT_IF_GOTO,
#endif
};

struct CRE_Event
{
	//piece of data telling the engine what do to with this information
	CREEventCode eventType;

	//generic unions to store data, function, and addresses
	genericData generic1;
	genericData generic2;
	genericData generic3;
	genericData generic4;

	//reference entity ID.
	unsigned int entityID;
};

//returns string version of the passed event code
//basically what you see in enum CRE_EVENT_CODE
string eventCodeToString(const CREEventCode& code);

#endif //EVENT_HPP