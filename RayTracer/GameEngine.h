#pragma once

#include "WindowHandler.h";
#include "World.h"

#include "Mesh.h";
#include "Sphere.h";
#include "Cube.h";
#include "Plane.h";

#include "material.h"
#include "lambertian.h"
#include "metal.h"



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
	int scale = 5;
	int ns = 50;
	
	//create a new window
	window = new WindowHandler(nx, ny, scale);

}

//handles the game starting
void GameEngine::startGame()
{	
	//create the world
	world = new World();

	//add a ground plane and a metal sphere
	//just to test
	world->addObject(new Item(vec3(0, 0, 0), new PlaneMesh(vec3(0, 0, 0), 10, vec3(0, 1, 0), vec3(0, 0, -1), new lambertian(vec3(0.6, 0.8, 0.0)))));
	
	Item* cube = new Item(vec3(0, 1, 0), new CubeMesh(vec3(0, 0, 0), 1, new lambertian(vec3(0.1, 0.1, 0.8))));
	cube->transform.scale = 0.5;
	world->addObject(cube);

	
	Item* sphere = new Item(vec3(-2, 1, 0), new SphereMesh(vec3(0, 0, 0), 1, new metal(vec3(0.5, 0.5, 0.5), 1)));
	sphere->transform.scale = 1;
	world->addObject(sphere);
	gameLoop();

}

//handles all functions executed for each loop of the game
void GameEngine::gameLoop()
{
	
	int cameraAngle = 0;
	float c_dist = -10;

	bool exitFlag = false;
	while (!exitFlag) {
		SDL_Event e;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT: exitFlag = true; break;

			case SDL_KEYDOWN:
				cameraAngle = (cameraAngle + 10) % 360;
				break;
			}
		}


		world->cam->transform.position = vec3(sin(cameraAngle * DEG2RAD) * c_dist, 1.5, cos(cameraAngle * DEG2RAD) * c_dist);
		world->cam->transform.rotation = vec3(0, cameraAngle, 0);


		//calculate the image of the current frame
		//and display it on the window
		world->render(window);
		window->renderWindow();
	}
}
