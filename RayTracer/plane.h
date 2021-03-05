#pragma once
#include <math.h>

#include "hitable.h"
#include "material.h"

class plane : public hitable {
public:
	plane() {}
	plane(vec3 cen, float r, vec3 f, vec3 u, material *m) : center(cen), radius(r), facing(f), up(u), mat(m) {};

	virtual bool hit(const ray& r, float tmin, float tmax, hyperspace *hs, hit_record& rec) const;
	vec3 center;
	float radius;
	vec3 facing;
	vec3 up;
	material* mat;
};

bool plane::hit(const ray& r, float t_min, float t_max, hyperspace *hs, hit_record& rec) const {
	
	float denom = dot(-r.direction(), facing);

	if (denom > 1e-6) {

		vec3 p0l0 = r.origin() -center;
		float temp = dot(p0l0, facing) / denom;

		
		if (temp > t_min && temp < t_max)
		{
			vec3 p = r.point_at_parameter(temp);
			vec3 v = p - center;
			vec3 right = cross(facing, up);
						

			if (dot(right * radius, v) <= radius 
				&& dot(-right * radius, v) <= radius
				&& dot(up * radius, v) <= radius
				&& dot(-up * radius, v) <= radius)
			{
				rec.mat_ptr = mat;
				rec.normal = facing;
				rec.t = temp;
				rec.p = p;

				return true;
			}
		}

	}

	return false;
}