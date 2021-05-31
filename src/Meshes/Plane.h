#pragma once
#include <math.h>

#include "Mesh.h"

//Plane mesh handler
class PlaneMesh : public Mesh {
public:
	//constructor
	PlaneMesh(Vec3 f=Vec3(0,0,-1), float w=1, Vec3 u = Vec3(0,1,0), Vec3 cen = Vec3(0, 0, 0)) : center(cen), width(w), facing(f), up(u){};

	//override
	bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

	
	Vec3 center;
	float width;
	Vec3 facing;
	Vec3 up;
};

//hit override
bool PlaneMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	
	//Math is based off of the plane generation from "A minimal ray-tracer"
	Vec3 tfmFacing = transform->applyTransform(facing);
	
	float denom = dot(-r.direction(), tfmFacing);

	if (abs(denom) > 1e-6) {

		Vec3 globalCenter = transform->applyTransform(center, true);

		Vec3 p0l0 = r.origin() - globalCenter;
		float temp = dot(p0l0, tfmFacing) / denom;

		
		if (temp > t_min && temp < t_max)
		{
			Vec3 tfmUp = transform->applyTransform(up);


			Vec3 p = r.point_at_parameter(temp);
			Vec3 v = p - globalCenter;

			Vec3 right = cross(facing, up);
			Vec3 tfmRight = transform->applyTransform(right);

			
			float scaled_width = (width / 2) * abs(dot(right, transform->scale));
			float scaled_height = (width /2) * abs(dot(up, transform->scale));


			//if the distance from the interesection and the point is within the radius, 
			//count as a hit

			tfmRight.make_unit_vector();
			tfmUp.make_unit_vector();

			if (dot(tfmRight, v) <= scaled_width
				&& dot(-tfmRight, v) <= scaled_width
				&& dot(tfmUp, v) <= scaled_height
				&& dot(-tfmUp, v) <= scaled_height)
			{
				
				rec.normal = unit_vector(tfmFacing);
				rec.t = temp;
				rec.p = p;

				return true;
			}
			
		}

	}

	return false;
}