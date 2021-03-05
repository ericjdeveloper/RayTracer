#pragma once
#include <stdio.h>
#include <math.h>

#include "hitable_list.h"
#include "material.h"
#include "plane.h"
#include "sphere.h"
#include "lambertian.h"
class cube : public hitable {
public:
	cube() {}
	cube(vec3 cen, float r, material *m) : center(cen), radius(r), mat(m) {
		

		faces[0] = new plane(center + vec3(radius, 0, 0),  radius, vec3(1, 0,0),   vec3(0, 1, 0), mat);
		faces[1] = new plane(center + vec3(-radius, 0, 0), radius, vec3(-1, 0, 0), vec3(0, 1, 0), mat);
		faces[2] = new plane(center + vec3(0, radius, 0),  radius, vec3(0, 1, 0),  vec3(0, 0, -1), mat);
		faces[3] = new plane(center + vec3(0, -radius, 0), radius, vec3(0, -1, 0), vec3(0, 1, -1), mat);
		faces[4] = new plane(center + vec3(0, 0, radius),  radius, vec3(0, 0, 1),  vec3(0, 1, 0), mat);
		faces[5] = new plane(center + vec3(0, 0, -radius), radius, vec3(0, 0, -1), vec3(0, 1, 0), mat);

		
		sides = new hitable_list(faces, 6);
	};

	virtual bool hit(const ray& r, float tmin, float tmax, hyperspace *hs, hit_record& rec) const;
	vec3 center;
	float radius;
	material* mat;
	hitable_list *sides;
	hitable *faces[6];
};

bool cube::hit(const ray& r, float t_min, float t_max, hyperspace *hs, hit_record& rec) const {

	return sides->hit(r, t_min, t_max, hs, rec);
}

