#include "hdr/Input.h"
#include "hdr/ColdEventDispatcher.h"
#include "hdr/Observable.h"
#include <cstring>
#include "hdr/Gui.h"

Input::Input(ColdEventDispatcher& ced_) : ced(&ced_)
{
	inputReset();
}

void Input::inputUpdate()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))

	{
		switch (event.type)
		{
		case SDL_QUIT:
			quit = 1;
			break;
		case SDL_KEYDOWN:
			key[event.key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			key[event.key.keysym.scancode] = 0;
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				wheelup = 1;
			if (event.wheel.y < 0)
				wheeldown = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftclic = 1;
				leftclic_position_x = event.motion.x;
				leftclic_position_y = event.motion.y;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				rightclic = 1;
				rightclic_position_x = event.motion.x;
				rightclic_position_y = event.motion.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftclic = 0;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				rightclic = 0;
			}
			break;
		case SDL_MOUSEMOTION:
			mousex = event.motion.x;
			mousey = event.motion.y;
			break;
		case SDL_DROPFILE:
			filedrop = event.drop.file;
			break;
		case SDL_WINDOWEVENT:
			switch (event.window.event)
			{
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				
				break;
			case SDL_WINDOWEVENT_RESIZED:
				ScreenEvent se;
				se.wWidth = event.window.data1;
				se.wHeight = event.window.data2;
				ced->notifyObservers(se);
				
			default:
				break;
			}
		default:
			break;
		}

		// Mouse Wheel Reset
		if (event.wheel.y == 0)
		{
			wheelup = 0;
			wheeldown = 0;
		}
	}
}

void Input::inputReset()
{
	auto ced2 = ced;
	memset(this, 0, sizeof(Input));
	ced = ced2;
}