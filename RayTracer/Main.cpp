#include <iostream>
#include <fstream>
#include <string>
#include <float.h>

#include "SDL2/SDL.h"

#include "sphere.h"
#include "cube2.h"
#include "plane.h"
#include "hitable_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "hypertube.h"


vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		float randx = ((double)rand() / (RAND_MAX + 1));
		float randy = ((double)rand() / (RAND_MAX + 1));
		float randz = ((double)rand() / (RAND_MAX + 1));
		p = 2.0*vec3(randx,randy,randz) - vec3(1, 1, 1);
		
	} while (p.squared_length() >= 1);
	

	return p;
}

vec3 color(const ray& r, hitable *world, hyperspace *hs, int depth) {

	hit_record rec;

	if (world->hit(r, 0.001, FLT_MAX, hs, rec)) {
		ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.mat_ptr->scatter(r, rec.p, rec.normal, attenuation, scattered)) {
			return attenuation * color(scattered, world, hs, depth + 1);
		}
		else {
			return vec3(0, 0, 0);
		}
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);

	}
}

int main(int argc, char* argv[])
{

	int nx = 200;
	int ny = 100;
	int ns = 50;

	int scale = 4;

	//SDL window creation
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("RTR", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, nx * scale, ny * scale, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	hypertube *ht = new hypertube();

	hitable *list[4];
	sphere* character = new sphere(vec3(1, 1, -2), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[0] = character;
	list[1] = 
		//new sphere(vec3(0, -1, -3), 1, 
	    new cube( vec3(3, -3, -5), 1,
			new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1.5,0.5,-1.5), 0.5, new metal(vec3(0.8, 0.0, 0.0), 0.0));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new metal(vec3(0.0, 0.0, 0.8), 0.5));

	hitable *world = new hitable_list(list, 4);

	camera cam;

	while(true){
		for (int j = 0; j < ny; j++)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 col(0, 0, 0);

				for (int s = 0; s < ns; s++) {

					float randx = ((double)rand() / (RAND_MAX + 1));
					float randy = ((double)rand() / (RAND_MAX + 1));

					float u = float(i + randx) / float(nx);
					float v = float(j + randy) / float(ny);
					ray r = cam.get_ray(u, v);
					vec3 p = r.point_at_parameter(2.0);
					col += color(r, world, ht, 0);

				}
				col /= float(ns);
				col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
				Uint8 ir = Uint8(255.99 * col[0]);
				Uint8 ig = Uint8(255.99 * col[1]);
				Uint8 ib = Uint8(255.99 * col[2]);


				SDL_SetRenderDrawColor(renderer, ir, ig, ib, 1);

				for (int x = 0; x < scale; x++)
				{
					for (int y = 0; y < scale; y++)
					{
						SDL_RenderDrawPoint(renderer, (i * scale)+x, ((ny - j)* scale) + y);
					}
				}
				

			}

		}

		SDL_RenderPresent(renderer);


		//character->center -= vec3(0, 0.1f, 0);
	}


	return 0;
}