#pragma once
#include <stdio.h>
#include <math.h>

#include "Mesh.h"
#include "Plane.h"

//cube override for the mesh
class CubeMesh : public Mesh {
public:
	CubeMesh(float s=1, vec3 cen = vec3(0,0,0)) : center(cen), size(s){
		
		//create a new plane for each face
		faces[0] = new PlaneMesh(vec3(1, 0, 0),  size, vec3(0, 1, 0),  center + vec3(size / 2, 0, 0));
		faces[1] = new PlaneMesh(vec3(-1, 0, 0), size, vec3(0, 1, 0),  center + vec3(-size / 2, 0, 0));
		faces[2] = new PlaneMesh(vec3(0, 1, 0),  size, vec3(0, 0, -1), center + vec3(0, size / 2, 0));
		faces[3] = new PlaneMesh(vec3(0, -1, 0), size, vec3(0, 1, -1), center + vec3(0, -size / 2, 0));
		faces[4] = new PlaneMesh(vec3(0, 0, 1),  size, vec3(0, 1, 0),  center + vec3(0, 0, size / 2));
		faces[5] = new PlaneMesh(vec3(0, 0, -1), size, vec3(0, 1, 0),  center + vec3(0, 0, -size / 2));


	};
	void setTransform(Transform *tfm) {
		transform = tfm;

		faces[0]->setTransform(transform);
		faces[1]->setTransform(transform);
		faces[2]->setTransform(transform);
		faces[3]->setTransform(transform);
		faces[4]->setTransform(transform);
		faces[5]->setTransform(transform);
	};

	bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	vec3 center;
	float size;
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

