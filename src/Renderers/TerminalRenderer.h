#pragma once

#include <stdlib.h>

#include "Renderer.h"
#include "../Vector.h"

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
	const char ASCII_CHARS[12] = {' ', '.',',',':', ';','+','*','?','%','S','#','@'};

	int getCharacterIndex(Uint8 r, Uint8 g, Uint8 b);
	
};

TerminalRenderer::TerminalRenderer(int w, int h)
{
	width = w;
	height = h;
	ios_base::sync_with_stdio(false);
}

void TerminalRenderer::renderWindow(ScreenData* sd)
{
	char screenBuffer[sd->getWidth() * 2 * sd->getHeight()];

	float scale_x = sd->getWidth() / width;
	float scale_y = sd->getHeight() / height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width * 2; x++)
		{
			int screen_x = floor(x * scale_x / 2);
			int screen_y = floor(y * scale_y);

			Uint8 r, g, b;
			sd->getPixel(screen_x, screen_y, r, g, b);

			int index = getCharacterIndex(r, g, b);				
			screenBuffer[y * (width * 2) + x] = ASCII_CHARS[index];


		}
	}


	cout << flush;
	system("cls");
	for (int y = height -1; y >= 0; y--)
	{
		char line[width * 2];
		for (int x =0; x < width * 2; x++)
		{
			//line[x] = screenBuffer[y * (width * 2) + x];
			cout << screenBuffer[y * (width * 2) + x];
		}

		cout << '\n';
	}

}

int TerminalRenderer::getCharacterIndex(Uint8 r, Uint8 g, Uint8 b)
{
	return (CHAR_COUNT-1) * (int)(r + g + b) / (255 * 3);
	// int saturation = max(max(r, g), b);
	// return (CHAR_COUNT - 1) * saturation / 255;
}



