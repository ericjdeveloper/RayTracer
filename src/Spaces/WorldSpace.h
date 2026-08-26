#pragma once

#include "..\Vector.h"
#include "..\Item.h"
#include "..\Materials\UVMap.h"

class WorldSpace {

public:
	WorldSpace() {
		envMat = new UVMap("gradient.ppm");
	}
	bool getColor(const Fan& f, Item **wrld_obs, int itm_cnt, int depth, Vector& color);
	Vector getEnvironmentColor(Vector coord);
private:
	virtual bool getHit(const Fan& f, Item *wrld_obs, float min_dist, float max_dist, hit_record& rec) =0;
	Material* envMat;
};

bool WorldSpace::getColor(const Fan& f, Item **wrld_obs, int itm_cnt, int depth, Vector& col)
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
		if (getHit(f, wrld_obs[i], 0.001, closest, rec)) {

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
	if (rec.mat_ptr->scatter(rec.r, rec.p, rec.normal, rec.UV_x, rec.UV_y, attenuation, scattered)) {
		//return the color of the scattered ray
		int newDepth = depth - 1;
		Fan scattered_fan = Fan(scattered.origin(), scattered.direction(), Vector(0,0,0,1),0);

		Vector scattered_color = Vector(1,1,1);
		if(!getColor(scattered_fan, wrld_obs, itm_cnt, newDepth, scattered_color))
		{
			scattered_color = getEnvironmentColor(scattered_fan.direction());
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
	
	// Vector texture_coordinate = Vector(sin(unit_direction.x()), sin(unit_direction.y()), sin(unit_direction.z()));
	// Vector norm = -coord;

	float vert = 0.5 * (1 + unit_direction.y() );
	Vector cloud_effect = Vector(0.5,0.3,0) * sin(unit_direction.z() * 10) * vert;		
	return vert * vert * (Vector(0.5f, 0.7f, 1.0f) + cloud_effect);	

	// Vector att;
	// Ray scatt;
	// envMat->scatter(Ray(Vector(0,0,0), coord), unit_direction, norm, coord.x(), coord.y(), att, scatt);
	// return att;
}