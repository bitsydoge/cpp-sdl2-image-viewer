#include "hdr/Window.h"

Window::Window(void)
{
	SDL_SetRenderDrawColor(render, 200, 60, 100, 0);
}

Window::~Window()
{
}

void Window::clear()
{
	SDL_SetRenderDrawColor(render, 200, 34, 65, 255);
	SDL_RenderClear(render);
}

void Window::renderDraw()
{
	SDL_RenderPresent(render);
}

SDL_Renderer* Window::getRenderer() const
{
	return render;
}

void Window::createWindow(int w, int h)
{
	SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &window, &render);
	width = w; height = h;
}