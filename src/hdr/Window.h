#pragma once
#include <SDL2/SDL.h>

class Window
{
	int width = 0, height = 0;
	SDL_Window *window = nullptr;
	SDL_Renderer *render = nullptr;
	SDL_DisplayMode current;

public:
	Window();
	~Window();
	void resize(int w, int h) { width = w; height = h; };
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	void clear();
	void renderDraw();
	SDL_Renderer* getRenderer() const;
	void createWindow(int w, int h);
};

