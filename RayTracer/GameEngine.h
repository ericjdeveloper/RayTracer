#pragma once

#include "WindowHandler.h";
#include "World.h"

#include "Mesh.h";
#include "Sphere.h";
#include "Cube.h";
#include "Plane.h";



//handles the various modules that have to do with
//the environment, as well as handles the driving
//of the start and loop
class GameEngine {
public:	
	GameEngine();
	//starts the game
	void startGame();

private:
	//the main loop of the game
	void gameLoop();

	//the output window
	WindowHandler *window;
	//the world object
	World *world;
};

//constructor
GameEngine::GameEngine()
{
	//set the window width, height, and scaling
	//set the sample size
	int nx = 200;
	int ny = 100;
	int scale = 4;
	int ns = 50;
	
	//create a new window
	window = new WindowHandler(nx, ny, scale);

}

//handles the game starting
void GameEngine::startGame()
{	

	//execute the game loop
	while (true)
	{
		gameLoop();
	}
}

//handles all functions executed for each loop of the game
void GameEngine::gameLoop()
{
	//calculate the image of the current frame
	//and display it on the window
	world->render(window);
	window->renderWindow();
}
