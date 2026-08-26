#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <float.h>


#include "Renderers\Renderer.h"
#include "Renderers\SDLWindowRenderer.h"
#include "Renderers\PPMRenderer.h"
#include "Renderers\TerminalRenderer.h"

#include "GameEngine.h"

//main function
//creates and launges the game engine
int main(int argc, char* argv[])
{
	int width = 400;
	int height = 200;
	int scale = 4;

	ScreenData* screen = new ScreenData(width, height);

	Renderer *rend = nullptr;
	if (argc >= 2)
	{
		if (argc >= 4)
		{
			if (argc >= 5)
				scale = atoi(argv[4]);

			width = atoi(argv[2]);
			height = atoi(argv[3]);
		}


		switch (*argv[1])
		{
			case 'a':
				rend = new TerminalRenderer(width * scale, height * scale);
				break;
			case 'i':
				rend = new PPMRenderer(width * scale, height * scale);
				break;
			default:
				rend = new SDLWindowRenderer(screen, scale);
		}
	}
	else
	{
		rend = new SDLWindowRenderer(screen, scale);
	}



	//initialize the game engine
	GameEngine *ge = new GameEngine(rend, 1, screen);

	//start it
	ge->startGame();


	return 0;
}