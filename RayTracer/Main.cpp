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

	Renderer* rend = new TerminalRenderer(width * scale, height * scale);

	//initialize the game engine
	GameEngine *ge = new GameEngine(rend, 1, width, height);

	//start it
	ge->startGame();
	
	return 0;
}