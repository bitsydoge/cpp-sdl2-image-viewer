#include <iostream>
#include "basic_sdl.h"

SDL_Color WHITE = { 255, 255, 255 };

extern int w_window;
extern int h_window;
extern int w_initial;
extern int h_initial;
extern int coef_window;

void affichage_gui(SDL_Renderer *render, SDL_Texture *gui, const char nom_du_fichier[])
{
	const std::string baseProgramPath(SDL_GetBasePath());
	SDL_Rect rect1 = { 0 }; SDL_Rect rect2 = { 0 };

	// // // // HAUT
	// Middle
	rect1 = {3,0,1,32};
	for (int i = 0; i < w_window; i++)
	{
		rect2 = { 0,0,i,32 };
		texToRenderPart(gui, render, &rect1, &rect2);
	}

	// Gauche
	rect1 = { 0,0,3,32 }; 	rect2 = { 0,0,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);

	// Droite
	rect1 = { 29,0,3,32 }; 	rect2 = { w_window-35,0,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);


	// // // // // // // // // // // // // // // // // // // // // // // //


	// // // // BAS
	// Middle
	rect1 = { 3,0,1,32 };
	for (int i = 0; i < w_window; i++)
	{
		rect2 = { 0,h_window+32,i,32 };
		texToRenderPart(gui, render, &rect1, &rect2);
	}

	// Gauche
	rect1 = { 0,0,3,32 }; 	rect2 = { 0,h_window+32,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);
	
	// Droite
	rect1 = { 29,0,3,32 }; 	rect2 = { w_window-3,h_window+32,3,32 };
	texToRenderPart(gui, render, &rect1, &rect2);

	// // // // // // // // // // //


	// // // // TEXTE

	SDL_Texture *ttf = nullptr;
	char temp[200] = "";
	sprintf_s(temp, "%s ", nom_du_fichier);
	ttf = txtToTex(temp, render, WHITE, 12);
	texToRender(ttf, render, 100, 4, 8);
	sprintf_s(temp, "Initial : %d x %d", w_initial, h_initial);
	SDL_DestroyTexture(ttf);
	ttf = txtToTex(temp, render, WHITE, 10);
	texToRender(ttf, render, 100, 4, h_window + 34);
	sprintf_s(temp, "Show : %d x %d (%d%%)", w_window, h_window, coef_window);
	SDL_DestroyTexture(ttf);
	ttf = txtToTex(temp, render, WHITE, 10);
	texToRender(ttf, render, 100, 4, h_window + 48);
	SDL_DestroyTexture(ttf);

	// //
	// Close button
	rect1 = { 32,0,32,32 }; 	rect2 = { w_window - 32,0,32,32 };
	texToRenderPart(gui, render, &rect1, &rect2);
}