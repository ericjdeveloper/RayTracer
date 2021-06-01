#pragma once

#include <thread>


#include "ScreenData.h"
#include "Item.h"
#include "Camera.h"
#include "Spaces/EuclideanSpace.h"

using namespace std;
//number of threads-per-axis to use
#define THREAD_COUNT 5


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
	Vec3 color(const ray&, int depth);

	//function for getting a random point within a unit sphere
	Vec3 random_in_unit_sphere();



	void renderSection(ScreenData* output, float x, float y, float w, float h);
};

World::World()
{
	//initialize camera object
	cam = new Camera(Vec3 (0, 1, -3));

	///lw = new LiminalWorld();
	ws = new EuclideanSpace();
}

//function for getting a random point within a unit sphere
Vec3 World::random_in_unit_sphere() {
	//the point to return
	Vec3 p;
	
	//get random values for p while the distance between p and
	//the center is larger than 1
	do {
		float randx = ((double)rand() / (RAND_MAX + 1));
		float randy = ((double)rand() / (RAND_MAX + 1));
		float randz = ((double)rand() / (RAND_MAX + 1));
		p = 2.0*Vec3(randx, randy, randz) - Vec3(1, 1, 1);

	} while (p.squared_length() >= 1);


	return p;
}

//gets the color value for a given ray
Vec3 World::color(const ray& r, int depth) {



	//create color variable
	Vec3 col = Vec3(0, 0, 0);

	if (!ws->getColor(r, world_objects, item_count, cam->max_bounces, col))
	{
		//background color
		Vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		
		col = (1.0f - t)*Vec3(1, 1, 1) + t * Vec3(0.5f, 0.7f, 1.0f);;//Vec3(0.0f, .28f, .98f);
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
		renderSection(output, 0,0,1, 1);
#else
		//get the percentage that each thread takes
		float thread_chunk = 1.0f / THREAD_COUNT;
		//create an array to store the threads
		thread threads[THREAD_COUNT * THREAD_COUNT];

		//loop through the chunks to assign the threads 
		for (int i = 0; i < THREAD_COUNT; i++)
		{
			for (int j = 0; j < THREAD_COUNT; j++)
			{
				//create a thread and assign it the current chunk (with proper offset)
				threads[(i * THREAD_COUNT) + j] = thread(&World::renderSection, this, output, i * thread_chunk, j  * thread_chunk, thread_chunk, thread_chunk);
			}
		}

		//loop through all the threads and wait for them to complete
		for (int i = 0; i < THREAD_COUNT * THREAD_COUNT; i++)
		{
			threads[i].join();
		}
#endif
}

void World::renderSection(ScreenData* output, float x, float y, float w, float h)
{
	//get the number of pixels to output
	int width = output->getWidth();
	int height = output->getHeight();

	//loop through the width
	for (int j = x * width; j < (x + w) * width; j++)
	{
		//loop through the height
		for (int i = y * height; i < (y + h) * height; i++)
		{
			//set a base color
			Vec3 col(0, 0, 0);

			//repeat this for each sample
			for (int s = 0; s < cam->samples; s++) {

				//get a random x and y value within the pixel
				float randx = ((double)rand() / (RAND_MAX + 1));
				float randy = ((double)rand() / (RAND_MAX + 1));
				

				//determine the point the ray should go through
				float u = float(j + randx) / float(width);
				float v = float(i + randy) / float(height);

				//gets a ray from the camera starting
				//at the cameras position and going through point u,v
				ray r = cam->get_ray(u, v);

				//get the color value for the given ray

				col += color(r, 0);

				

			}
			//divide the color by the number of samples
			col /= float(cam->samples);
			
			//gamma adjustment
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			//get the Uint8 values
			Uint8 ir = Uint8(255.99 * col[0]);
			Uint8 ig = Uint8(255.99 * col[1]);
			Uint8 ib = Uint8(255.99 * col[2]);

			//set the given pixel value of the output
			
			output->setPixel(j, i, ir, ig, ib);

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