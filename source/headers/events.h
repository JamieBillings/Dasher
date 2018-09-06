#ifndef EVENTS_INCLUDED
#define EVENTS_INCLUDED

namespace Events
{
	SDL_Event event;

	int mouse_x = 0;
	int mouse_y = 0;

	bool GetEvents();

}

#endif