#pragma once

#include <chrono>
using namespace std::chrono;

#include "Renderers\\Renderer.h"
#include "World.h"

#include "Meshes\\Mesh.h"
#include "Meshes\\Sphere.h"
#include "Meshes\\Cube.h"
#include "Meshes\\Plane.h"

#include "Materials\Material.h"
#include "Materials\Lambertian.h"
#include "Materials\Metal.h"

#define SAMPLE_COUNT 20

//handles the various modules that have to do with
//the environment, as well as handles the driving
//of the start and loop
class GameEngine {
public:	
	GameEngine(Renderer* rends, int r_cnt, int screen_width, int screen_height);
	//starts the game
	void startGame();

private:
	//the main loop of the game
	void gameLoop();

	//the output window
	ScreenData *output;

	int r_count;
	Renderer* renderers;

	//the world object
	World *world;
};

//constructor
GameEngine::GameEngine(Renderer *rends, int r_cnt, int screen_width, int screen_height)
{
	r_count = r_cnt;
	renderers = rends;

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




	world->addObject(new Item(Vec3(0, 0, 0), new PlaneMesh(Vec3(0, 1, 0), 5, Vec3(0, 0, -1)), new Lambertian(Vec3(0.6, 0.8, 0.0))));
	

	Item* cube = new Item(Vec3(0, 0.5, 0), new CubeMesh(), new Lambertian(Vec3(0.8, 0.1, 0.2)));
	cube->transform.scale = Vec3(0.5, 0.5, 0.5);
	world->addObject(cube);
	
	Item* sphere = new Item(Vec3(1, 0.5, 5), new SphereMesh(), new Metal(Vec3(0.3, 0.5, 0.1), 0.3));
	sphere->transform.scale = Vec3(0,3,0);
	world->addObject(sphere);
	//*/

	

/*	//add the liminal volumes
	LiminalVolume* vol_plane1 = new LiminalVolume(Vec3(0, 0.5, -1.5), new PlaneMesh(Vec3(0,0,-1)), Vec3(1,1,0.3));
	vol_plane1->transform.scale = Vec3(1, 1, 1);
	world->lw->addVolume(vol_plane1);

	LiminalVolume* vol_plane2 = new LiminalVolume(Vec3(0, 0.5, 1.5), new PlaneMesh(Vec3(0,0,1)), Vec3(1, 1, 0.3));
	vol_plane2->transform.scale = Vec3(1, 1, 1);
	world->lw->addVolume(vol_plane2);
*/


	Item* wall1 = new Item(Vec3(-0.5, 0.5, 0), new PlaneMesh(Vec3(-1,0,0)), new Lambertian(Vec3(0.1, 0.1, 0.8)));
	wall1->transform.scale = Vec3(1, 1, 3);
	world->addObject(wall1);

	Item* wall2 = new Item(Vec3(0.5, 0.5, 0), new PlaneMesh(Vec3(1,0,0)), new Lambertian(Vec3(0.1, 0.1, 0.8)));
	wall2->transform.scale = Vec3(1, 1, 3);
	world->addObject(wall2);

	Item* wall3 = new Item(Vec3(0, 1, 0), new PlaneMesh(Vec3(0,1,0), 1, Vec3(0,0,1)), new Lambertian(Vec3(0.1, 0.1, 0.8)));
	wall3->transform.scale = Vec3(1, 1, 3);
	world->addObject(wall3);




	gameLoop();

}

//handles all functions executed for each loop of the game
void GameEngine::gameLoop()
{

	int cameraAngle = 0;
	float c_dist = -3;

	bool exitFlag = false;

	
	while (!exitFlag) {
		auto start = high_resolution_clock::now();

		SDL_Event e;

		/*
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
		*/

		cameraAngle = cameraAngle + 5;
		
		if (cameraAngle == 360)
		{
			exitFlag = true;
			continue;
		}


		world->cam->transform.position = Vec3(sin(cameraAngle * DEG2RAD) * c_dist, 0.5, cos(cameraAngle * DEG2RAD) * c_dist);
		world->cam->transform.rotation = Vec3(0, cameraAngle, 0);


		//calculate the image of the current frame
		//and display it on the window
		world->render(output);
		
		for (int i = 0; i < r_count; i++)
		{
			renderers[i].renderWindow(output);
		}


		auto end = high_resolution_clock::now();

		duration<double> elapsed = end - start;

		cout << 1 / elapsed.count() << "\n";

		
	}
}
