#pragma once

#include "..\Vector.h"
#include "..\Item.h"

class WorldSpace {

public:
	bool getColor(const Ray& r, Item **wrld_obs, int itm_cnt, int depth, Vector& color);
	Vector getEnvironmentColor(Vector coord);
private:
	virtual bool getHit(const Ray& r, Item *wrld_obs, float min_dist, float max_dist, hit_record& rec) =0;
};

bool WorldSpace::getColor(const Ray& r, Item **wrld_obs, int itm_cnt, int depth, Vector& col)
{
	if(depth == 0)	
		return false;	

	float closest = FLT_MAX;
	float closest_index = -1;


	//record data for a hit point on the ray
	hit_record rec;

	//loop through all the items in the world
	//and find the closest
	for (int i = 0; i < itm_cnt; i++) {

		//if the item registers a hit
		if (getHit(r, wrld_obs[i], 0.001, closest, rec)) {

			closest = rec.t;
			closest_index = i;

		}

	}

	//if no object is hit, return false
	if (closest_index == -1){
		return false;
	}

	//create a new reflection ray
	Ray scattered;
	Vector attenuation;

	//if the number of bounces is under the threshold
	//and the scatter results in another hit
	if (rec.mat_ptr->scatter(r, rec.p, rec.normal, rec.UV_x, rec.UV_y, attenuation, scattered)) {
		//return the color of the scattered ray
		int newDepth = depth - 1;

		Vector scattered_color = Vector(1,1,1);
		if(!getColor(scattered, wrld_obs, itm_cnt, newDepth, scattered_color))
		{
			scattered_color = getEnvironmentColor(r.direction());
		}		

		col = attenuation * scattered_color;		
	}
	else {
		col = attenuation;
	}

	return true;

}

Vector WorldSpace::getEnvironmentColor(Vector coord)
{	
	Vector unit_direction = unit_vector(coord);
	float t = 0.5*(unit_direction.y() + 1.0);		
	return t * Vector(0.5f, 0.7f, 1.0f);	
}