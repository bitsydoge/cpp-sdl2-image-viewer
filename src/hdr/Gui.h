#pragma once
#include <SDL2/SDL.h>
#include "Observer.h"
#include "ScreenEvent.h"
#include "ColdEventDispatcher.h"

class Gui : 
	public Observer<ScreenEvent>
{
	SDL_Color WHITE = { 255, 255, 255 };
	int windowWidth;
	int windowHeight;
	bool onScreenEvent(ScreenEvent & screenEvent);

public:
	Gui(ColdEventDispatcher& ced);
	~Gui();
	void affichage_gui(SDL_Renderer *render, SDL_Texture *gui, const char nom_du_fichier[]);

};
