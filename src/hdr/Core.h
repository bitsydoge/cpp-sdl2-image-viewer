#pragma once
#include <string>
#include "Gui.h"
#include "Image.h"
#include "Input.h"
#include "Window.h"

class Core
{
	std::string programPath;

public:
	Core();
	~Core();
	std::string path() const;

	ColdEventDispatcher ced;

	Gui gui;
	Image image;
	Input input;
	Window window;

};
