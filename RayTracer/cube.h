#pragma once
#include <stdio.h>
#include <math.h>

#include "Mesh.h"
#include "material.h"
#include "Plane.h"

//cube override for the mesh
class CubeMesh : public Mesh {
public:
	CubeMesh() {}
	CubeMesh(vec3 cen, float r, material *m) : center(cen), radius(r), mat(m) {
		
		//create a new plane for each face
		faces[0] = new PlaneMesh(center + vec3(radius, 0, 0),  radius, vec3(1, 0,0),   vec3(0, 1, 0), mat);
		faces[1] = new PlaneMesh(center + vec3(-radius, 0, 0), radius, vec3(-1, 0, 0), vec3(0, 1, 0), mat);
		faces[2] = new PlaneMesh(center + vec3(0, radius, 0),  radius, vec3(0, 1, 0),  vec3(0, 0, -1), mat);
		faces[3] = new PlaneMesh(center + vec3(0, -radius, 0), radius, vec3(0, -1, 0), vec3(0, 1, -1), mat);
		faces[4] = new PlaneMesh(center + vec3(0, 0, radius),  radius, vec3(0, 0, 1),  vec3(0, 1, 0), mat);
		faces[5] = new PlaneMesh(center + vec3(0, 0, -radius), radius, vec3(0, 0, -1), vec3(0, 1, 0), mat);

	};

	bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float radius;
	material* mat;
	Mesh *faces[6];
};

//cube override
bool CubeMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {


	hit_record temp_rec;

	//just loop through all the faces
	//and calculate
	bool hit_anything = false;
	double closest_so_far = t_max;
	for (int i = 0; i < 6; i++)
	{
		if (faces[i]->hit(r, t_min, closest_so_far, temp_rec)) {
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

