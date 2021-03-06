#pragma once

#include "WorldSpace.h"


class EuclideanSpace : public WorldSpace {
public:
	bool getColor(const ray& r, Item **wrld_ob, int itm_cnt, int depth, Vec3& color);
};


bool EuclideanSpace::getColor(const ray& r, Item **wrld_obs, int itm_cnt, int depth, Vec3& col)
{

	float closest = FLT_MAX;
	float closest_index = -1;


	//record data for a hit point on the ray
	hit_record rec;

	//loop through all the items in the world
	//and find the closest
	for (int i = 0; i < itm_cnt; i++) {

		//if the item registers a hit
		if (wrld_obs[i]->hit(r, 0.001, closest, rec)) {

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
	Vec3 attenuation;

	//if the number of bounces is under the threshold
	//and the scatter results in another hit
	if (depth > 0 && rec.mat_ptr->scatter(r, rec.p, rec.normal, attenuation, scattered)) {
		//return the color of the scattered ray
		int newDepth = depth - 1;

		Vec3 scattered_color = Vec3(1,1,1);
		getColor(scattered, wrld_obs, itm_cnt, newDepth, scattered_color);

		col = attenuation * scattered_color;		
	}
	else {
		col = Vec3(1,1,1);
	}

	return true;

}