#include "hdr/Gui.h"
#include <SDL2/SDL.h>
#include "hdr/Texture.h"
#include <functional>
#include "hdr/Window.h"
#include "hdr/Observable.h"
#include "hdr/ColdEventDispatcher.h"
#include <iostream>

Gui::Gui(ColdEventDispatcher& ced) :
	Observer(std::bind(&Gui::onScreenEvent, this, std::placeholders::_1), ced), windowWidth(0), windowHeight(0)
{
}

Gui::~Gui()
{
	
}

bool Gui::onScreenEvent(ScreenEvent& screenEvent) {
	windowWidth = screenEvent.wWidth;
	windowHeight = screenEvent.wHeight;
	return true;
}

void Gui::affichage_gui(SDL_Renderer *render, SDL_Texture *gui, const char nom_du_fichier[])
{
	SDL_Rect rect1 = { 0 }; SDL_Rect rect2 = { 0 };

	// // // // HAUT
	// Middle
	rect1 = { 3,0,1,32 };
	for (int i = 0; i < windowWidth; i++)
	{
		rect2 = { 0,0,i,32 };
		texToRenderPart(gui, render, &rect1, &rect2);
	}

	// Gauche
	rect1 = { 0,0,3,32 }; 	rect2 = { 0,0,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);

	// Droite
	rect1 = { 29,0,3,32 }; 	rect2 = { windowWidth - 35,0,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);


	// // // // // // // // // // // // // // // // // // // // // // // //


	// // // // BAS
	// Middle
	rect1 = { 3,0,1,32 };
	for (int i = 0; i < windowWidth; i++)
	{
		rect2 = { 0,windowHeight + 32,i,32 };
		texToRenderPart(gui, render, &rect1, &rect2);
	}

	// Gauche
	rect1 = { 0,0,3,32 }; 	rect2 = { 0,windowHeight + 32,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);

	// Droite
	rect1 = { 29,0,3,32 }; 	rect2 = { windowWidth - 3,windowHeight + 32,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);

	// // // // // // // // // // //


	// // // // TEXTE

	SDL_Texture *ttf = nullptr;
	char temp[200] = "";
	sprintf_s(temp, "%s ", nom_du_fichier);
	ttf = txtToTex(temp, render, WHITE, 12);
	texToRender(ttf, render, 100, 4, 8);
	//sprintf_s(temp, "Initial : %d x %d", w_initial, h_initial);
	SDL_DestroyTexture(ttf);
	ttf = txtToTex(temp, render, WHITE, 10);
	texToRender(ttf, render, 100, 4, windowHeight + 34);
	//sprintf_s(temp, "Show : %d x %d (%d%%)", windowWidth, windowHeight, coef_window);
	SDL_DestroyTexture(ttf);
	ttf = txtToTex(temp, render, WHITE, 10);
	texToRender(ttf, render, 100, 4, windowHeight + 48);
	SDL_DestroyTexture(ttf);

	// //
	// Close button
	rect1 = { 32,0,32,32 }; 	rect2 = { windowWidth - 32,0,32,32 };
	texToRenderPart(gui, render, &rect1, &rect2);
}
