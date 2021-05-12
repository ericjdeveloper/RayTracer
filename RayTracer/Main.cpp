#include <iostream>
#include <fstream>
#include <string>
#include <float.h>

#include "SDLWindowRenderer.h"
#include "PPMRenderer.h"
#include "TerminalRenderer.h"
#include "GameEngine.h"

//main function
//creates and launges the game engine
int main(int argc, char* argv[])
{
	int width = 100;
	int height = 50;
	int scale = 1;


	Renderer *rend = nullptr;
	if (argc == 2)
	{
		switch (*argv[1])
		{
			case 'a':
				rend = new TerminalRenderer(width * scale, height * scale);
				break;
			case 'i':
				rend = new PPMRenderer(width * scale, height * scale);
				break;
			default:
				rend = new SDLWindowRenderer(width * scale, height * scale);
		}
	}
	else
	{
		rend = new SDLWindowRenderer(width * scale, height * scale);
	}

	//initialize the game engine
	GameEngine *ge = new GameEngine(rend, 1, width, height);

	//start it
	ge->startGame();
	
	return 0;
}