#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "define.h"
#include "basic_sdl.h"
#include "event.h"
#include "gui.h"

int w_window(0), h_window(0), coef_window(100);
int w_initial(0), h_initial(0);

int main(int argc, char **argv) {
	const std::string baseProgramPath(SDL_GetBasePath());
	char path_du_fichier[300] = "no_file.jpg";
	if (argc > 1)
	{
		strcpy_s(path_du_fichier, argv[1]);
	}
	double temp_coef1(0), temp_coef2(0);
	SDL_DisplayMode current;
	SDL_Window *window = nullptr;
	SDL_Renderer *render = nullptr;
	SDL_Texture *tex = nullptr;
	SDL_Texture *gui = nullptr;
	Input INPUT; inputInit(&INPUT);
	INPUT.filedrop = "";

	initVid(&window, &render, 0, 0);
	SDL_SetWindowTitle(window, "ColdViewer");
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	TTF_Init();
	SDL_GetCurrentDisplayMode(0, &current);
	gui = imgToTex((baseProgramPath + "gui.bmp").c_str(), render);
	tex = imgToTex(path_du_fichier, render);

	SDL_QueryTexture(tex, nullptr, nullptr, &w_window, &h_window);
	SDL_QueryTexture(tex, nullptr, nullptr, &w_initial, &h_initial);
	
	if (current.w*80/100.0 < w_initial)
		temp_coef1 = int(current.w * 80 / 100.0 / w_initial * 100);
	if (current.h*80/100.0 < h_initial+64)
		temp_coef2 = int(current.h*80/100.0 / h_initial * 100);

	if (temp_coef1 < temp_coef2 && temp_coef1 != 0)
		coef_window = int(temp_coef1);
	if (temp_coef2 <= temp_coef1 && temp_coef2 != 0)
		coef_window = int(temp_coef2);

	SDL_SetWindowPosition(window, 50, 50);

	SDL_SetWindowSize(window, w_window*static_cast<double>(coef_window) / 100, h_window*static_cast<double>(coef_window) / 100 + 64);
	clearWithColor(render, 0, 0, 0, 255);
	texToRender(tex, render, coef_window, 0, 32);

	w_window = w_initial*(static_cast<double>(coef_window) / 100);
	h_window = h_initial*(static_cast<double>(coef_window) / 100);
	
	std::string nom_du_fichier;
	std::string temp_nom_du_fichier;
	std::size_t lastSlashPos;

	temp_nom_du_fichier = path_du_fichier;
	lastSlashPos = temp_nom_du_fichier.find_last_of("\\");
	if(lastSlashPos != std::string::npos)
	{
		nom_du_fichier = temp_nom_du_fichier.substr(lastSlashPos+1);
	}
	affichage_gui(render, gui, nom_du_fichier.c_str());
	SDL_RenderPresent(render);

	// Limiter FPS
	int FPS(120), TICKS(1000 / FPS);
	long start(SDL_GetTicks()), actual(SDL_GetTicks());
	// Boucle Principal
	while(!INPUT.quit && !INPUT.key[SDL_SCANCODE_ESCAPE] && !(INPUT.leftclic && INPUT.leftclic_position_x > w_window - 32 && INPUT.leftclic_position_y < 32))
	{
		actual = SDL_GetTicks();
		if (actual - start > TICKS)
		{
			inputReturn(&INPUT);

			if (INPUT.key[SDL_SCANCODE_UP] || INPUT.wheelup && !INPUT.rightclic) // SCALE UP
			{

					coef_window+=1;
					if (INPUT.wheelup)
						coef_window += 8;
					if (coef_window <= 10)
						coef_window = 10;
					w_window = w_initial*(static_cast<double>(coef_window) / 100);
					h_window = h_initial*(static_cast<double>(coef_window) / 100);
					SDL_SetWindowSize(window, w_window, h_window + 64);
					clearWithColor(render, 0, 0, 0, 255);
					texToRender(tex, render, coef_window, 0, 32);
					affichage_gui(render, gui, nom_du_fichier.c_str());
					SDL_RenderPresent(render);
			}
			if (INPUT.key[SDL_SCANCODE_DOWN] || INPUT.wheeldown && !INPUT.rightclic) // SCALE DOWN
			{
				if (static_cast<double>(coef_window) / 100 * w_window > 200 || static_cast<double>(coef_window) / 100 * h_window > 200)
				{
					coef_window-=1;
					if (INPUT.wheeldown)
						coef_window -= 8;
				    if (coef_window <= 10)
						coef_window = 10;
					w_window = w_initial*(static_cast<double>(coef_window) / 100);
					h_window = h_initial*(static_cast<double>(coef_window) / 100);
					SDL_SetWindowSize(window, w_window, h_window + 64);
					clearWithColor(render, 0, 0, 0, 255);
					texToRender(tex, render, coef_window, 0, 32);
					affichage_gui(render, gui, nom_du_fichier.c_str());
					SDL_RenderPresent(render);
				}
			}
			if (INPUT.key[SDL_SCANCODE_RETURN]) // SCALE RESET
			{
					coef_window = 100;
					w_window = w_initial*(static_cast<double>(coef_window / 100));
					h_window = h_initial*(static_cast<double>(coef_window / 100));
					SDL_SetWindowSize(window, w_window, h_window + 64);
					clearWithColor(render, 0, 0, 0, 255);
					texToRender(tex, render, coef_window, 0, 32);
					affichage_gui(render, gui, nom_du_fichier.c_str());
					SDL_RenderPresent(render);
				
			}
			if (INPUT.rightclic) // WINDOW MOVE
			{
				int x_mouse_screen; int y_mouse_screen;
				SDL_GetGlobalMouseState(&x_mouse_screen, &y_mouse_screen);
				SDL_SetWindowPosition(window, x_mouse_screen - INPUT.rightclic_position_x, y_mouse_screen - INPUT.rightclic_position_y);
				inputReturn(&INPUT);
			}

			if (INPUT.filedrop != "")
			{
				coef_window = 100;
				strcpy_s(path_du_fichier, INPUT.filedrop);
				tex = imgToTex(path_du_fichier, render);
				SDL_QueryTexture(tex, nullptr, nullptr, &w_window, &h_window);
				SDL_QueryTexture(tex, nullptr, nullptr, &w_initial, &h_initial);

				if (current.w * 80 / 100.0 < w_initial)
					temp_coef1 = int(current.w * 80 / 100.0 / w_initial * 100);
				if (current.h * 80 / 100.0 < h_initial + 64)
					temp_coef2 = int(current.h * 80 / 100.0 / h_initial * 100);

				if (temp_coef1 < temp_coef2 && temp_coef1 != 0)
					coef_window = int(temp_coef1);
				if (temp_coef2 <= temp_coef1 && temp_coef2 != 0)
					coef_window = int(temp_coef2);

				SDL_SetWindowSize(window, w_window*static_cast<double>(coef_window) / 100, h_window*static_cast<double>(coef_window) / 100 + 64);

				w_window = w_window*static_cast<double>(coef_window) / 100;
				h_window = h_window*static_cast<double>(coef_window) / 100;

				clearWithColor(render, 0, 0, 0, 255);
				texToRender(tex, render, coef_window, 0, 32);

				temp_nom_du_fichier = path_du_fichier;
			    lastSlashPos = temp_nom_du_fichier.find_last_of("\\");
				if (lastSlashPos != std::string::npos)
				{
					nom_du_fichier = temp_nom_du_fichier.substr(lastSlashPos + 1);
				}
					
				affichage_gui(render, gui, nom_du_fichier.c_str());
				SDL_RenderPresent(render);
			}
			INPUT.filedrop = "";
			start = actual;
		}
		else
		{
			SDL_Delay(TICKS-(actual-start));
		}
	}

	if (nullptr != tex)
		SDL_DestroyTexture(tex);
	if (nullptr != render)
		SDL_DestroyRenderer(render);
	if (nullptr != window)
		SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}