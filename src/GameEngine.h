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




	world->addObject(new Item(Vector(0, 0, 0), new PlaneMesh(Vector(0, 1, 0), 5, Vector(0, 0, -1)), new Lambertian(Vector(0.6, 0.8, 0.0))));
	

	Item* cube = new Item(Vector(0, 0.5, 0), new CubeMesh(), new Lambertian(Vector(0.8, 0.1, 0.2)));
	cube->transform.scale = Vector(0.5, 0.5, 0.5);
	world->addObject(cube);
	
	Item* sphere = new Item(Vector(1, 0.5, 5), new SphereMesh(), new Metal(Vector(0.3, 0.5, 0.1), 0.3));
	sphere->transform.scale = Vector(0,3,0);
	world->addObject(sphere);
	//*/

	

/*	//add the liminal volumes
	LiminalVolume* vol_plane1 = new LiminalVolume(Vector(0, 0.5, -1.5), new PlaneMesh(Vector(0,0,-1)), Vector(1,1,0.3));
	vol_plane1->transform.scale = Vector(1, 1, 1);
	world->lw->addVolume(vol_plane1);

	LiminalVolume* vol_plane2 = new LiminalVolume(Vector(0, 0.5, 1.5), new PlaneMesh(Vector(0,0,1)), Vector(1, 1, 0.3));
	vol_plane2->transform.scale = Vector(1, 1, 1);
	world->lw->addVolume(vol_plane2);
*/


	Item* wall1 = new Item(Vector(-0.5, 0.5, 0), new PlaneMesh(Vector(-1,0,0)), new Lambertian(Vector(0.1, 0.1, 0.8)));
	wall1->transform.scale = Vector(1, 1, 3);
	world->addObject(wall1);

	Item* wall2 = new Item(Vector(0.5, 0.5, 0), new PlaneMesh(Vector(1,0,0)), new Lambertian(Vector(0.1, 0.1, 0.8)));
	wall2->transform.scale = Vector(1, 1, 3);
	world->addObject(wall2);

	Item* wall3 = new Item(Vector(0, 1, 0), new PlaneMesh(Vector(0,1,0), 1, Vector(0,0,1)), new Lambertian(Vector(0.1, 0.1, 0.8)));
	wall3->transform.scale = Vector(1, 1, 3);
	world->addObject(wall3);




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
			//spin the camera
			cameraAngle = cameraAngle + 5;

			//update the camera position
			world->cam->transform.position = Vector(sin(cameraAngle * DEG2RAD) * c_dist, 0.5, cos(cameraAngle * DEG2RAD) * c_dist);
			world->cam->transform.rotation = Vector(0, cameraAngle, 0);


			//if the thread is still alive,
			//join it back
			if(renderThread != nullptr)
				renderThread->join();

			//set rendering to true,
			//and create a new thread
			isRendering = true;
			renderThread = new thread(GameEngine::render, this); 
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
