#pragma once
#include <math.h>

#include "Mesh.h"
#include "material.h"

//Plane mesh handler
class PlaneMesh : public Mesh {
public:
	//constructor
	PlaneMesh(vec3 cen, float r, vec3 f, vec3 u, material *m) : center(cen), radius(r), facing(f), up(u), mat(m) {};

	//override
	bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

	
	vec3 center;
	float radius;
	vec3 facing;
	vec3 up;
	material* mat;
};

//hit override
bool PlaneMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	
	//Math is based off of the plane generation from "A minimal ray-tracer"
	vec3 tfmFacing = transform->applyTransform(facing);
	float tfmRadius = radius * transform->scale;

	float denom = dot(-r.direction(), tfmFacing);

	if (denom > 1e-6) {

		vec3 globalCenter = transform->applyTransform(center, true);

		vec3 p0l0 = r.origin() - globalCenter;
		float temp = dot(p0l0, tfmFacing) / denom;

		
		if (temp > t_min && temp < t_max)
		{
			vec3 tfmUp = transform->applyTransform(up);


			vec3 p = r.point_at_parameter(temp);
			vec3 v = p - globalCenter;
			vec3 right = unit_vector(cross(tfmFacing, tfmUp)) * transform->scale;

			//if the distance from the interesection and the point is within the radius, 
			//count as a hit
			float r_sqd = tfmRadius * tfmRadius;


			if (dot(right * radius, v) <= r_sqd
				&& dot(-right * radius, v) <= r_sqd
				&& dot(tfmUp * radius, v) <= r_sqd
				&& dot(-tfmUp * radius, v) <= r_sqd)
			{

				rec.mat_ptr = mat;
				rec.normal = tfmFacing;
				rec.t = temp;
				rec.p = p;

				return true;
			}
		}

	}

	return false;
}