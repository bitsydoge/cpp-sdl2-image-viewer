#pragma once
#include <cstring>
#include <SDL2/SDL.h>
#include "define.h"
#include <iostream>

void inputReturn(Input *INPUT)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))

	{
		switch (event.type)
		{
		case SDL_QUIT:
			INPUT->quit = 1;
			break;
		case SDL_KEYDOWN:
			INPUT->key[event.key.keysym.scancode] = 1;
			break;
		case SDL_KEYUP:
			INPUT->key[event.key.keysym.scancode] = 0;
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.y > 0)
				INPUT->wheelup = 1;
			if (event.wheel.y < 0)
				INPUT->wheeldown = 1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				INPUT->leftclic = 1;
				INPUT->leftclic_position_x = event.motion.x;
				INPUT->leftclic_position_y = event.motion.y;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				INPUT->rightclic = 1;
				INPUT->rightclic_position_x = event.motion.x;
				INPUT->rightclic_position_y = event.motion.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				INPUT->leftclic = 0;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
			{
				INPUT->rightclic = 0;
			}
			break;
		case SDL_MOUSEMOTION:
			INPUT->mousex = event.motion.x;
			INPUT->mousey = event.motion.y;
			break;
		case SDL_DROPFILE:
			INPUT->filedrop = event.drop.file;
			break;
		default:
			break;
		}

		// Mouse Wheel Reset
		if (event.wheel.y == 0)
		{
			INPUT->wheelup = 0;
			INPUT->wheeldown = 0;
		}
	}
}

void inputInit(Input *INPUT)
{
	memset(INPUT, 0, sizeof(Input));
}