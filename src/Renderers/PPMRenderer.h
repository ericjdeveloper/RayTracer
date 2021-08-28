#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"
#include "Vector.h"

class PPMRenderer : public Renderer {
public:	
	//constructor that sets the width, height, and scale of the window
	PPMRenderer(int w, int h);
	//function for rendering the window
	void renderWindow(ScreenData* sd);
private:
	int width, height;
	int fn;
};

PPMRenderer::PPMRenderer(int w, int h)
{
	width = w;
	height = h;
	fn = 0;
}

void PPMRenderer::renderWindow(ScreenData* sd)
{
	float scale_x = sd->getWidth()  / width;
	float scale_y = sd->getHeight() / height;
	std::ofstream imgFile;
	imgFile.open("frames/f" + std::to_string(fn) + ".ppm");

	imgFile << "P3\n" << width << " " << height << "\n255\n";
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			int screen_x = floor(x * scale_x);
			int screen_y = floor(y * scale_y);

			Uint8 r, g, b;
			sd->getPixel(screen_x, screen_y, r, g, b);
			imgFile << (int)r << " " << (int)g << " " << (int)b << "\n";

		}
	}
	imgFile.close();
}



