#pragma once

#include "WindowHandler.h"
#include "Item.h"
#include "Camera.h"



//object to handle the Entities in the world
//and how to render them
class World {
public:
	//empty constructor
	World();

	//calculates the pixel values for all of output
	void render(WindowHandler* output);
	//adds an object to the list
	void addObject(Item* item);

	//the world camera
	Camera *cam;

private:
	//the list of world objects
	Item **world_objects;

	//the number of items in world_objects
	int item_count;

	//function for obtaining the color of the given ray
	vec3 color(const ray&, int depth);

	//function for getting a random point within a unit sphere
	vec3 random_in_unit_sphere();
};

World::World()
{
	//initialize camera object
	cam = new Camera(vec3 (0, 1.5, -5));
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

	//record data for a hit point on the ray
	hit_record rec;

	if (item_count == 0)
	{
		
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
		
	}

	
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	vec3 col = (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);

	
	float closest = FLT_MAX;



	//loop through all the items in the world
	for (int i = 0; i < item_count; i++) {

		//if the item registers a hit
		if (world_objects[i]->mesh->hit(r, 0.001, closest, rec)) {
			//create a new reflection ray
			ray scattered;
			vec3 attenuation;

			//if the number of bounces is under the threshold
			//and the scatter results in another hit
			if (depth < cam->max_bounces && rec.mat_ptr->scatter(r, rec.p, rec.normal, attenuation, scattered)) {
				//return the color of the scattered ray
				col = attenuation * color(scattered, depth + 1);
			}
			else {
				col = vec3(0, 0, 0);
			}


			closest = rec.t;
		}
		
	}

	return col;

	
	
	
}

//determines the value for each pixel and sets it to output
void World::render(WindowHandler* output)
{
	//get the number of pixels to output
	int width = output->getWidth();
	int height = output->getHeight();

	//loop through the width
	for (int j = 0; j < width; j++)
	{
		//loop through the height
		for (int i = 0; i < height; i++)
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