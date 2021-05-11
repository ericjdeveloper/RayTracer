#pragma once

#include <stdlib.h>

#include "Renderer.h"
#include "vec3.h"

using namespace std;

class TerminalRenderer : public Renderer {
public:
	//constructor that sets the width, height, and scale of the window
	TerminalRenderer(int w, int h);
	//function for rendering the window
	void renderWindow(ScreenData* sd);
private:
	int width, height;

	//thanks to Kite for the character selection... check him out on youtube!
	const int CHAR_COUNT = 12;
	const char ASCII_CHARS[12] = {'@', '#', 'S', '%', '?', '*', '+', ';', ':', ',', '.', ' '};

	int getCharacterIndex(Uint8 r, Uint8 g, Uint8 b);
	
};

TerminalRenderer::TerminalRenderer(int w, int h)
{
	width = w;
	height = h;
}

void TerminalRenderer::renderWindow(ScreenData* sd)
{
	cout << "flushing." << flush;
	system("CLS");


	float scale_x = sd->getWidth() / width;
	float scale_y = sd->getHeight() / height;

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			int screen_x = floor(x * scale_x);
			int screen_y = floor(y * scale_y);

			Uint8 r, g, b;
			sd->getPixel(screen_x, screen_y, r, g, b);

			int index = getCharacterIndex(r, g, b);
			//note, done twice as characters are ~twice as high as they are wide				
			cout << ASCII_CHARS[index] << ASCII_CHARS[index];


		}
		cout << '\n';
	}

}

int TerminalRenderer::getCharacterIndex(Uint8 r, Uint8 g, Uint8 b)
{
	return (int)(CHAR_COUNT * ((int)r + (int)g + (int)b) / (255 * 3));
}



