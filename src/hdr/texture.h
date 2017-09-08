#pragma once
#include <SDL2/SDL.h>

SDL_Texture *imgToTex(const char path[], SDL_Renderer *render);
SDL_Texture *txtToTex(const char path[], SDL_Renderer *render, SDL_Color color, int coef);
void texToRender(SDL_Texture* tex, SDL_Renderer *render, int coef, int x, int y);
void texToRenderPart(SDL_Texture* tex, SDL_Renderer *render, SDL_Rect *rect1, SDL_Rect *rect2);
