#pragma once
#include <math.h>

#include "Mesh.h"

//Plane mesh handler
class PlaneMesh : public Mesh {
public:
	//constructor
	PlaneMesh(Vector f=Vector(0,0,-1), float w=1, Vector u = Vector(0,1,0), Vector cen = Vector(0, 0, 0)) : center(cen), width(w), facing(f), up(u){};

	//override
	bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	Vector getUVCoordinate(Vector hitPoint) const;

	Vector center;
	float width;
	Vector facing;
	Vector up;
};

//hit override
bool PlaneMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	
	//Math is based off of the plane generation from "A minimal ray-tracer"
	Vector tfmFacing = transform->applyTransform(facing);
	
	float denom = dot(-r.direction(), tfmFacing);

	if (abs(denom) > 1e-6) {

		Vector globalCenter = transform->applyTransform(center, true);

		Vector p0l0 = r.origin() - globalCenter;
		float temp = dot(p0l0, tfmFacing) / denom;

		
		if (temp > t_min && temp < t_max)
		{
			Vector tfmUp = transform->applyTransform(up);


			Vector p = r.point_at_parameter(temp);
			Vector v = p - globalCenter;

			Vector right = cross(facing, up);
			Vector tfmRight = transform->applyTransform(right);

			
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
				Vector uv_coords = getUVCoordinate(p);
				rec.UV_x = uv_coords.x();
				rec.UV_y = uv_coords.y();
				return true;
			}
			
		}

	}

	return false;
}


Vector PlaneMesh::getUVCoordinate(Vector hitPoint) const
{
	Vector down = transform->applyTransform(-up);
	Vector left = cross(down,transform->applyTransform(facing));
	Vector delta = hitPoint - transform->applyTransform(center, true);

	float xlength = dot(left, delta);
	float ylength = dot(down, delta);
	Vector uvCoord = Vector( (xlength / width) + 0.5f,(ylength / width) + 0.5f ,0);


	return uvCoord;
}