#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Core
{
private:
    std::string programPath;

public:
    std::string path(){return programPath;};
    void sdl_init()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
    }
    void sdl_quit()
    {
        TTF_Quit();
        SDL_Quit();
    }
};

class Window
{
private:
    int width=0, height=0;
    SDL_Window *window = nullptr;
    SDL_Renderer *render = nullptr;
    SDL_DisplayMode current;

public:
    int getWidth(){return width;}
    int getHeight(){return height;}
    int clearWithColor(int r, int g, int b, int a)
    {
        if (SDL_SetRenderDrawColor(render, r, g, b, a) < 0)
            return -1;
        if (SDL_RenderClear(render) < 0)
            return -1;
        return 0;
    }
};

class Image
{
private:
    int width=0, height=0;
    float zoom=100;
    char path_du_fichier[300] = "no_file.jpg";

public:
    int getWidth(){return width;}
    int getHeight(){return height;}
    int getZoom(){return zoom;}
};

class Input
{
public:

    char key[SDL_NUM_SCANCODES];
    int wheelup;
    int wheeldown;
    int quit;
    int leftclic;
    int leftclic_position_x;
    int leftclic_position_y;
    int rightclic;
    int rightclic_position_x;
    int rightclic_position_y;
    int mousex;
    int mousey;
    char *filedrop;

    void inputUpdate()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))

        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    key[event.key.keysym.scancode] = 1;
                    break;
                case SDL_KEYUP:
                    key[event.key.keysym.scancode] = 0;
                    break;
                case SDL_MOUSEWHEEL:
                    if (event.wheel.y > 0)
                        wheelup = 1;
                    if (event.wheel.y < 0)
                        wheeldown = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        leftclic = 1;
                        leftclic_position_x = event.motion.x;
                        leftclic_position_y = event.motion.y;
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        rightclic = 1;
                        rightclic_position_x = event.motion.x;
                        rightclic_position_y = event.motion.y;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        leftclic = 0;
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        rightclic = 0;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    mousex = event.motion.x;
                    mousey = event.motion.y;
                    break;
                case SDL_DROPFILE:
                    filedrop = event.drop.file;
                    break;
                default:
                    break;
            }

            // Mouse Wheel Reset
            if (event.wheel.y == 0)
            {
                wheelup = 0;
                wheeldown = 0;
            }
        }
    }

    void inputInit(Input *INPUT)
    {
        memset(INPUT, 0, sizeof(Input));
    }
};

int main(int argc, char **argv)
{
    Core core; Window window; Image image; Input input;
    core.sdl_init();


    input.inputUpdate();

    core.sdl_quit();
    return 0;
}