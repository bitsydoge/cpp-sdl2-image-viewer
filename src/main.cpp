#pragma once
#include "hdr/Core.h"
#include "hdr/Texture.h"

int main(int argc, char **argv)
{
	Core core;
    core.window.createWindow(300, 364);
	
	ScreenEvent se;
	se.wWidth = core.window.getWidth();
	se.wHeight = core.window.getHeight();
	core.ced.notifyObservers(se);

	SDL_Texture *gui = imgToTex("img/gui.bmp", core.window.getRenderer());

    while(!core.input.key[SDL_SCANCODE_ESCAPE] && !core.input.quit)
    {
        core.window.clear();
		core.input.inputUpdate();
		core.gui.affichage_gui(core.window.getRenderer(), gui, "YO");
		core.window.renderDraw();
    }
    return 0;
}
