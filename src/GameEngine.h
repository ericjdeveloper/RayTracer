#pragma once

#include <chrono>
using namespace std::chrono;

#include <thread>
using namespace std;

#include "Renderers\\Renderer.h"
#include "World.h"

#include "Meshes\\Mesh.h"
#include "Meshes\\Sphere.h"
#include "Meshes\\Cube.h"
#include "Meshes\\Plane.h"

#include "Materials\Material.h"
#include "Materials\Lambertian.h"
#include "Materials\Metal.h"
#include "Materials\UVMap.h"

#define SAMPLE_COUNT 5

//handles the various modules that have to do with
//the environment, as well as handles the driving
//of the start and loop
class GameEngine {
public:	
	GameEngine(Renderer* rends, int r_cnt, int screen_width, int screen_height);
	//starts the game
	void startGame();

	void render();

	bool isRendering = false;

	Item* testItem;
private:
	//the main loop of the game
	void gameLoop();

	//the output window
	ScreenData *output;

	int r_count;
	Renderer* renderers;

	//the world object
	World *world;

	thread *renderThread;

};

//constructor
GameEngine::GameEngine(Renderer *rends, int r_cnt, int screen_width, int screen_height)
{
	r_count = r_cnt;
	renderers = rends;
	renderThread = nullptr;

	//create a new window
	output = new ScreenData(screen_width, screen_height);

}

//handles the game starting
void GameEngine::startGame()
{	

	//create the world
	world = new World();
	world->cam->samples = SAMPLE_COUNT;
	//add a ground plane and a metal sphere
	//just to test

	world->cam->transform.position = Vector(0, 0, -3);


	//world->addObject(new Item(Vector(0, 0, 0), new PlaneMesh(Vector(0, 1, 0), 5, Vector(0, 0, -1)), new Lambertian(Vector(0.6, 0.8, 0.0))));
	

	Item* cube = new Item(Vector(0, 0, 0), new CubeMesh(), new UVMap("sample_1.ppm"));
	testItem = cube;
	cube->transform.scale = Vector(1,1,1);
	world->addObject(cube);
	
	/*
	Item* sphere = new Item(Vector(0,0,0, 1), new SphereMesh(), new Metal(Vector(0.3, 0.5, 0.1), 0.3));
	world->addObject(sphere);
	//*/

/*
	Item* wall1 = new Item(Vector(-0.5, 0.5, 0), new PlaneMesh(Vector(-1,0,0)), new Lambertian(Vector(0.1, 0.1, 0.8)));
	wall1->transform.scale = Vector(1, 1, 3);
	world->addObject(wall1);

	Item* wall2 = new Item(Vector(0.5, 0.5, 0), new PlaneMesh(Vector(1,0,0)), new Lambertian(Vector(0.1, 0.1, 0.8)));
	wall2->transform.scale = Vector(1, 1, 3);
	world->addObject(wall2);

	Item* wall3 = new Item(Vector(0, 1, 0), new PlaneMesh(Vector(0,1,0), 1, Vector(0,0,1)), new Lambertian(Vector(0.1, 0.1, 0.8)));
	wall3->transform.scale = Vector(1, 1, 3);
	world->addObject(wall3);
*/



	gameLoop();

}

//handles all functions executed for each loop of the game
void GameEngine::gameLoop()
{
	//variable for holding the camera angle
	float cameraAngle = 0;
	//distance that the camera is from the focus point 
	float c_dist = -3;

	//flag to determine whether to exit the program
	bool exitFlag = false;

	int fCount = 0;

	//main game loop
	while (!exitFlag) {

		//event holder
		SDL_Event e;

		//while events continue to occur
		while (SDL_PollEvent(&e))
		{
			//handle events differently based on the input
			switch (e.type)
			{
			//if the x button is pressed, closed the application
			case SDL_QUIT: exitFlag = true; break;

			}
		}
		
		//if we are not currently rendering a frame
		//update the world
		if(!isRendering)
		{



			//update the camera position

			/*
			//spinning camera
			world->cam->transform.position = Vector(sin(cameraAngle * DEG2RAD) * c_dist, 0, cos(cameraAngle * DEG2RAD) * c_dist);
			world->cam->transform.rotation[0] = Vector(0, -cameraAngle, 0);
			//world->cam->transform.rotation[1] = Vector(0,0,45);
			//*/

			//world->cam->transform.position = Vector(0.0,0.5,-1 - 0.02 * cameraAngle);
			//world->cam->transform.rotation[1] = Vector(0,0,45);


			 testItem->transform.rotation[0] = Vector(cameraAngle,cameraAngle,0);


			//if the thread is still alive,
			//join it back
			if(renderThread != nullptr)
				renderThread->join();

			//set rendering to true,
			//and create a new thread
			isRendering = true;
			renderThread = new thread(GameEngine::render, this); 
/*
			if(fCount == 360 / 5)
			{
				exitFlag = true;
				break;
			}
//*/
			//spin the camera
			cameraAngle = cameraAngle + 5;
			fCount++;
		}

	}

}

//render function called in separate thread
void GameEngine::render()
{
	//render the current world to the output screen
	world->render(output);

	//go through each renderer and output respectively
	for (int i = 0; i < r_count; i++)
	{
		renderers[i].renderWindow(output);
	}

	//set the rendering flag
	isRendering = false;
}
