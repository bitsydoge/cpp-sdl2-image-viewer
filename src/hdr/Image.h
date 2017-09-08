#pragma once
class Image
{
	int width = 0, height = 0;
	float zoom = 100;
	char path_du_fichier[300] = "no_file.jpg";

public:
	Image();
	~Image();
	int getWidth();
	int getHeight();
	int getZoom();
};

