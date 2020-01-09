#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL_events.h>

//CRE Events are altered and simplified versions of SDL's internal event strucuts.
//This change was made to have an easier to use type of event thats still compatible with
//SDL Events.

//struct to hold CRE event data.
//Note that this is basically a rip off of SDL_UserEvent without information that
//goes unused is not included.
struct CRE_Event
{
	int eventType;
	int data1;
	int data2;
};

//converts CRE_Event to an SDL_Event
//copies over data from CRE_Event to SDL_UserEvent member of SDL_Event
SDL_Event convertCREtoSDL(const CRE_Event& event);

//frees the dynamic memory portion of user part of the passed SDL_Event*
void freeSDLUserEvent(SDL_Event* e);

//overloaded version of SDL_PushEvent to work with CRE events.
void SDL_PushEvent(CRE_Event* e);

#endif //EVENT_HPP