#pragma once

#include "vec3.h"
#include "ray.h"
#include "material.h"

//struct for the collision data of an object
struct hit_record {
	float t;
	vec3 p;
	vec3 normal;
	material *mat_ptr;
};

//Mesh class to handle rendering
class Mesh {
public:
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record& rec) const = 0;
};