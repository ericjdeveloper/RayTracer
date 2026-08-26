#pragma once

#include <thread>
#include <functional>

#include "ScreenData.h"
#include "Item.h"
#include "Camera.h"
#include "Spaces/EuclideanSpace.h"

using namespace std;
//number of threads-per-axis to use
#define CHUNK_SIZE 50


//object to handle the Entities in the world
//and how to render them
class World {
public:
	//empty constructor
	World();

	//calculates the pixel values for all of output
	void render(ScreenData* output);
	//adds an object to the list
	void addObject(Item* item);

	//the world camera
	Camera *cam;

	WorldSpace* ws;

private:
	//the list of world objects
	Item **world_objects;

	//the number of items in world_objects
	int item_count = 0;

	//function for obtaining the color of the given ray
	Vector color(const Fan&, int depth);

	//function for getting a random point within a unit sphere
	Vector random_in_unit_sphere();

	void renderSection(ScreenData* output, float x, float y, float w, float h);
};

World::World()
{
	//initialize camera object
	cam = new Camera(Vector (0, 1, -3));

	///lw = new LiminalWorld();
	ws = new EuclideanSpace();
}

//function for getting a random point within a unit sphere
Vector World::random_in_unit_sphere() {
	//the point to return
	Vector p;
	
	//get random values for p while the distance between p and
	//the center is larger than 1
	do {
		float randx = ((double)rand() / (RAND_MAX + 1));
		float randy = ((double)rand() / (RAND_MAX + 1));
		float randz = ((double)rand() / (RAND_MAX + 1));
		p = 2.0*Vector(randx, randy, randz) - Vector(1, 1, 1);

	} while (p.squared_length() >= 1);


	return p;
}

//gets the color value for a given ray
Vector World::color(const Fan& f, int depth) {

	//create color variable
	Vector col = Vector(0, 0, 0);

	if (!ws->getColor(f, world_objects, item_count, cam->max_bounces, col))
	{			
		col = ws->getEnvironmentColor(f.direction());	
	}
	return col;
	
}

//determines the value for each pixel and sets it to output
void World::render(ScreenData* output)
{
//determines whether to use this thread to render
//or to create a series of other renderers
#if THREAD_COUNT == 1
		//render the entire screen at once
		renderSection(output, 0,0,output->getWidth(), output->getHeight());
#else
		int chunk_count_x = ceil(output->getWidth() / CHUNK_SIZE);
		int chunk_count_y = ceil(output->getHeight() / CHUNK_SIZE);
		//create an array to store the threads
		thread threads[chunk_count_x * chunk_count_y];

		//loop through the chunks to assign the threads 
		for (int i = 0; i < chunk_count_x; i++)
		{
			for (int j = 0; j < chunk_count_y; j++)
			{
				int start_x = i * CHUNK_SIZE;
				int start_y = j * CHUNK_SIZE;
				//create a thread and assign it the current chunk (with proper offset)
				threads[(i * chunk_count_y) + j] = 
					thread(&World::renderSection, this, output,
						start_x,
						start_y,
						min(output->getWidth() - start_x, CHUNK_SIZE),
						min(output->getHeight() - start_y, CHUNK_SIZE)
					);
			}
		}

		//loop through all the threads and wait for them to complete
		for (int i = 0; i < chunk_count_x * chunk_count_y; i++)
		{
			threads[i].join();
		}
#endif
}

void World::renderSection(ScreenData* output, float x, float y, float w, float h)
{
	hash<int> sample_hasher;

	int width = output->getWidth();
	int height = output->getHeight();

	//loop through the width
	for (int j = 0; j < w; j++)
	{
		//loop through the height
		for (int i = 0; i < h; i++)
		{
			//set a base color
			Vector col(0, 0, 0);

			//repeat this for each sample
			for (int s = 0; s < cam->samples; s++) {

				//srand(j * (height * cam->samples) + i * cam->samples + s);
				//get a random x and y value within the pixel
				float randx = ((double)rand() / (RAND_MAX + 1));
				float randy = ((double)rand() / (RAND_MAX + 1));

				//determine the point the ray should go through
				float u = float(x + j + randx) / width;
				float v = float(y + i + randy) / height;

				//gets a ray from the camera starting
				//at the cameras position and going through point u,v
				Fan f = cam->get_fan(u, v);
				//get the color value for the given ray

				col += color(f, 0);

			}
			// //divide the color by the number of samples
			col /= float(cam->samples);
			
			//gamma adjustment
			col = Vector(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			//get the Uint8 values
			Uint8 ir = Uint8(255.99 * col[0]);
			Uint8 ig = Uint8(255.99 * col[1]);
			Uint8 ib = Uint8(255.99 * col[2]);

			//set the given pixel value of the output
			output->setPixel(x + j, y + i, ir, ig, ib);

		}

	}

}

//adds an object to the list of objects
void World::addObject(Item *item)
{

	
	//create a new list 1 item larger
	Item **new_obs = new Item*[item_count + 1];

	//loop through all the old items
	//and add them to the new list
	for (int i = 0; i < item_count; ++i)
	{
		new_obs[i] = world_objects[i];
	}

	//add the new item
	new_obs[item_count++] = item;

	//set the world_objects list to be this new list
	world_objects = new_obs;
	
}