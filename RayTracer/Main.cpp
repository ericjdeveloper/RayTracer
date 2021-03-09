#include <iostream>
#include <fstream>
#include <string>
#include <float.h>

#include "GameEngine.h"

//main function
//creates and launges the game engine
int main(int argc, char* argv[])
{
	//initialize the game engine
	GameEngine *ge = new GameEngine();

	//start it
	ge->startGame();
	
	return 0;
}