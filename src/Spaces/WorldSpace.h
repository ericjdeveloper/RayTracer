#pragma once

#include "Vector.h"
#include "Item.h"

class WorldSpace {

public:
	bool getColor(const ray& r, Item **wrld_obs, int itm_cnt, int depth, Vector& color);
private:
	virtual bool getHit(const ray& r, Item *wrld_obs, float min_dist, float max_dist, hit_record& rec) =0;
};

bool WorldSpace::getColor(const ray& r, Item **wrld_obs, int itm_cnt, int depth, Vector& col)
{

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
	ray scattered;
	Vector attenuation;

	//if the number of bounces is under the threshold
	//and the scatter results in another hit
	if (depth > 0 && rec.mat_ptr->scatter(r, rec.p, rec.normal, attenuation, scattered)) {
		//return the color of the scattered ray
		int newDepth = depth - 1;

		Vector scattered_color = Vector(1,1,1);
		getColor(scattered, wrld_obs, itm_cnt, newDepth, scattered_color);

		col = attenuation * scattered_color;		
	}
	else {
		col = Vector(1,1,1);
	}

	return true;

}