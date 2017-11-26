#pragma once
#include <SDL2/SDL.h>
#include "Observer.h"
#include "ScreenEvent.h"
#include "ColdEventDispatcher.h"

class Gui : 
	public Observer<ScreenEvent>
{
	SDL_Texture *texture_handle;
	SDL_Color WHITE = { 255, 255, 255 };
	int windowWidth;
	int windowHeight;
	bool onScreenEvent(ScreenEvent & screenEvent);

public:
	Gui(ColdEventDispatcher& ced);
	~Gui();
	void texture_load(SDL_Texture *texture);
	void affichage_gui(SDL_Renderer *render, const char nom_du_fichier[]);

};
