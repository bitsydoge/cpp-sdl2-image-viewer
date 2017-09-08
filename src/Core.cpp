#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "hdr/Core.h"

Core::Core(void): gui(ced), input(ced)
{
	programPath = SDL_GetBasePath();
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
}

Core::~Core()
{
	TTF_Quit();
	SDL_Quit();
}

std::string Core::path() const
{return programPath;}
