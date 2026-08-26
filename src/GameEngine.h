#pragma once

#include <chrono>
using namespace std::chrono;

#include <thread>
using namespace std;

#include "Renderers\\Renderer.h"
#include "World.h"

#include "Meshes\Mesh.h"
#include "Meshes\Sphere.h"
#include "Meshes\Cube.h"
#include "Meshes\Plane.h"

#include "Materials\Material.h"
#include "Materials\Normal.h"
#include "Materials\Depth.h"
#include "Materials\Lambertian.h"
#include "Materials\Luminous.h"
#include "Materials\Metal.h"
#include "Materials\UVMap.h"

#define SAMPLE_COUNT 30
#define MAX_BOUNCES 3

//handles the various modules that have to do with
//the environment, as well as handles the driving
//of the start and loop
class GameEngine {
public:	
	GameEngine(Renderer* rends, int r_cnt, ScreenData *screen);
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
GameEngine::GameEngine(Renderer *rends, int r_cnt, ScreenData* screen)
{
	r_count = r_cnt;
	renderers = rends;
	renderThread = nullptr;

	//create a new window
	output = screen;

}

//handles the game starting
void GameEngine::startGame()
{	

	//create the world
	world = new World();
	world->cam->samples = SAMPLE_COUNT;
	world->cam->max_bounces = MAX_BOUNCES;
	//add a ground plane and a metal sphere
	//just to test

	world->cam->transform.position = Vector(0, 1, -3);	
	world->cam->transform.rotation[1] = Vector(0,0,0);

	//world->addObject(new Item(Vector(0, 0, 0), new PlaneMesh(Vector(0, 1, 0), 5, Vector(0, 0, -1)), new Lambertian(Vector(0.6, 0.8, 0.0))));
	

	// new Metal(Vector(0.1,0.1,0.1), 0.1f)
	Item* floor = new Item(Vector(0,-0.5,0), new PlaneMesh(Vector(0,1,0), 5, Vector(0,0, -1)), new Depth());
	world->addObject(floor);

	//world->addObject(new Item(Vector(1,0,1), new CubeMesh(), new Lambertian(Vector(0.6,0.3,0.8))));
	
	//Item* sphere = new Item(Vector(2, 0, 0), new SphereMesh(), new UVMap("sample.ppm")); //
	Item* sphere = new Item(Vector(0, 0, 0), new SphereMesh(1, Vector(0,0,0,0)), new Depth());
	sphere->transform.scale = Vector(1,1,1);
	world->addObject(sphere);
	testItem = sphere;

	// Item* cube = new Item(Vector(10,0,0), new CubeMesh(1), new UVMap("gradient.ppm"));
	// world->addObject(cube);
	
	// Item* light = new Item(Vector(-1, 1, 1), new PlaneMesh(Vector(0, 1, 0), 1, Vector(0,0,-1)), new Luminous(Vector(1, 0.87, 0.13)));
	// light->transform.rotation[0] = Vector(45, 30, 30);
	// world->addObject(light);

	// Item* cubemap = new Item(Vector(3, 0, 3), new CubeMesh(), new UVMap("sample.ppm"));
	// testItem = cubemap;
	// cubemap->transform.scale = Vector(10,10,10);
	// world->addObject(cubemap);
	
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

	float deltaTime = 0.01;
	auto startFrameTimestamp = chrono::high_resolution_clock::now();

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
			case SDL_EVENT_QUIT: exitFlag = true; break;

			}
		}
		
		//if we are not currently rendering a frame
		//update the world
		if(!isRendering)
		{
			auto endFrameTimestamp = chrono::high_resolution_clock::now();
			std::chrono::duration<double> duration = endFrameTimestamp - startFrameTimestamp;
			deltaTime = duration.count();
			startFrameTimestamp = endFrameTimestamp;

			output->fps = 1.0 / deltaTime;
			//update the camera position

			
			//spinning camera
			world->cam->transform.position = Vector(sin(cameraAngle * DEG2RAD) * c_dist, 0.75f, cos(cameraAngle * DEG2RAD) * c_dist);
			// world->cam->viewport_plane = Vector(4.0, 2.0, 2.0, (sin(cameraAngle * DEG2RAD)));
			world->cam->transform.rotation[0] = Vector(0, -cameraAngle, 0);
			//world->cam->transform.rotation[1] = Vector(0,0,45);
			//*/

			//world->cam->transform.position = Vector(0.0,0.5,-1 - 0.02 * cameraAngle);
			//world->cam->transform.rotation[1] = Vector(0,0,45);
			testItem->transform.position = Vector(0, sin(cameraAngle * DEG2RAD),0);

			//testItem->transform.rotation[0] = Vector(cameraAngle,cameraAngle,0);			


			//if the thread is still alive,
			//join it back
			if(renderThread != nullptr)
				renderThread->join();

			//set rendering to true,
			//and create a new thread
			isRendering = true;
			renderThread = new thread(GameEngine::render, this); 
			this_thread::sleep_for(1000ms);

			//spin the camera
			cameraAngle += 10 * deltaTime;
			fCount++;
			//exitFlag = true;
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
