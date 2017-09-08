#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// CLASS CORE
//////////////////////////////////////////////////

class Core
{
private:
    std::string programPath;

public:
    std::string path(){return programPath;};
    Core();
    ~Core();
};

Core::Core(void)
{
    programPath = SDL_GetBasePath();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
}
Core::~Core()
{
    TTF_Quit();
    SDL_Quit();
}

// CLASS WINDOW
//////////////////////////////////////////////

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
    void clear()
    {
        SDL_RenderClear(render);
    }
    // Must be called only once
    void createWindow(int w, int h)
    {
        SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_RESIZABLE, &window, &render);
        width = w; height = h;
    }

    void renderDraw()
    {
        SDL_SetRenderDrawColor(render, 200,34,65,255);
        SDL_RenderPresent(render);
    }

    Window();   // This is the constructor

};

Window::Window(void)
{
    SDL_SetRenderDrawColor(render,200,60,100,0);
    std::cout << "HELLO" << std::endl;
}

// CLASS IMAGE
//////////////////////////////////////////////////

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

    Image();

};

Image::Image()
{

}

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

    void inputReset()
    {
        memset(this, 0, sizeof(Input));
    }

    Input();
};

Input::Input()
{
    inputReset();
}

///////// MAIN ///////////
//////////////////////////

int main(int argc, char **argv)
{
    Core core; Window window; Image image; Input input;
    window.createWindow(800, 480);

    while(!input.key[SDL_SCANCODE_ESCAPE] && !input.quit)
    {
        window.clear();
        input.inputUpdate();
        window.renderDraw();
    }

    return 0;
}