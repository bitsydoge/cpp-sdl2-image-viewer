#pragma once
#include <SDL2/SDL.h>

typedef struct Input
{
	char key[SDL_NUM_SCANCODES];
	int wheelup;
	int wheeldown;
	int quit;
	int leftclic;
	int leftclic_position_x;
	int leftclic_position_y;
	int rightclic;
	int rightclic_position_x;
	int rightclic_position_y;
	int mousex;
	int mousey;
	char *filedrop;
} Input;