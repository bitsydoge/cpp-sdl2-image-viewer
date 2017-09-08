#pragma once
#include <cstdio>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

SDL_Texture *imgToTex(const char path[], SDL_Renderer *render)
{
	SDL_Surface *tmp = nullptr;
	SDL_Texture *tex = nullptr;
	tmp = IMG_Load(path);
	if (tmp == nullptr)
	{
		fprintf(stderr, "Error IMG_Load : %s \n", SDL_GetError());
		return nullptr;
	}
	tex = SDL_CreateTextureFromSurface(render, tmp);
	if (nullptr == tex)
	{
		fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s \n", SDL_GetError());
		return nullptr;
	}
	SDL_FreeSurface(tmp);
	return tex;
}

SDL_Texture *txtToTex(const char path[], SDL_Renderer *render, SDL_Color color, int coef)
{
	const std::string baseProgramPath(SDL_GetBasePath());
	TTF_Font *police = TTF_OpenFont((baseProgramPath + "FiraSans-Medium.ttf").c_str(), coef);
	if (police == nullptr)
	{
		fprintf(stderr, "Error TTF_OpenFont : %s \n", TTF_GetError());
		return nullptr;
	}

	SDL_Surface *tmp = nullptr;
	tmp = TTF_RenderText_Blended(police, path, color);
	if (tmp == nullptr)
	{
		fprintf(stderr, "Error TTF_RenderText_Blended : %s \n", SDL_GetError());
		return nullptr;
	}

	SDL_Texture *tex = nullptr;
	tex = SDL_CreateTextureFromSurface(render, tmp);
	if (nullptr == tex)
	{
		fprintf(stderr, "Error SDL_CreateTextureFromSurface : %s \n", SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(tmp);
	TTF_CloseFont(police);
	return tex;
}

void texToRender(SDL_Texture* tex, SDL_Renderer *render, int coef, int x, int y)
{
	auto w(0), h(0);
	SDL_Rect rect = { 0 };
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	rect.h = h*static_cast<double>(coef) / 100; rect.w = w*static_cast<double>(coef) / 100;
	rect.x = x; rect.y = y;
	SDL_RenderCopy(render, tex, nullptr, &rect);
}

void texToRenderPart(SDL_Texture* tex, SDL_Renderer *render, SDL_Rect *rect1, SDL_Rect *rect2)
{
	// RECT1 = Qu'est ce qui est selection� sur la texture XY et WH
	// RECT2 = Ou est plac� sur le render la texture et sa taille (d�forme)
	SDL_RenderCopy(render, tex, rect1, rect2);
}
