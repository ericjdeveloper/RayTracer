#pragma once

#include <thread>


#include "ScreenData.h"
#include "Item.h"
#include "Camera.h"
#include "Spaces/EuclideanSpace.h"

using namespace std;
#define THREAD_CHUNK 0.1


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
	vec3 color(const ray&, int depth);

	//function for getting a random point within a unit sphere
	vec3 random_in_unit_sphere();



	void renderSection(ScreenData* output, float x, float y, float w, float h);
};

World::World()
{
	//initialize camera object
	cam = new Camera(vec3 (0, 1, -3));

	///lw = new LiminalWorld();
	ws = new EuclideanSpace();
}

//function for getting a random point within a unit sphere
vec3 World::random_in_unit_sphere() {
	//the point to return
	vec3 p;
	
	//get random values for p while the distance between p and
	//the center is larger than 1
	do {
		float randx = ((double)rand() / (RAND_MAX + 1));
		float randy = ((double)rand() / (RAND_MAX + 1));
		float randz = ((double)rand() / (RAND_MAX + 1));
		p = 2.0*vec3(randx, randy, randz) - vec3(1, 1, 1);

	} while (p.squared_length() >= 1);


	return p;
}

//gets the color value for a given ray
vec3 World::color(const ray& r, int depth) {



	//create color variable
	vec3 col = vec3(0, 0, 0);

	if (!ws->getColor(r, world_objects, item_count, cam->max_bounces, col))
	{
		//background color
		///vec3 unit_direction = unit_vector(r.direction());
		///float t = 0.5*(unit_direction.y() + 1.0);
		///(1.0f - t)*vec3(1, 1, 1) + t * vec3(0.5f, 0.7f, 1.0f);
		col = vec3(0.0f, .28f, .98f);
	}


	return col;
	
}

//determines the value for each pixel and sets it to output
void World::render(ScreenData* output)
{
	//the number of threads to use;
	const int thread_axis_count = 1 / THREAD_CHUNK;

	thread threads[thread_axis_count * thread_axis_count];


	for (int i = 0; i < thread_axis_count; i++)
	{
		for (int j = 0; j < thread_axis_count; j++)
		{
			threads[(i * thread_axis_count) + j] = thread(&World::renderSection, this, output, i * THREAD_CHUNK, j * THREAD_CHUNK, THREAD_CHUNK, THREAD_CHUNK);
		}
	}
	
	
	for (int i = 0; i < thread_axis_count * thread_axis_count; i++)
	{
		threads[i].join();
	}
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
			vec3 col(0, 0, 0);

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
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

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