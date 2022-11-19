#pragma once
#include <stdio.h>
#include <math.h>

#include "Mesh.h"
#include "Plane.h"

//cube override for the mesh
class CubeMesh : public Mesh {
public:
	CubeMesh(float s=1, Vector cen = Vector(0,0,0)) : center(cen), size(s){};


	void setTransform(Transform *tfm) {
		transform = tfm;
	};

	bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
	Vector getUVCoordinate(Vector hitPoint) const;
	Vector center;
	float size;
};

//cube override
bool CubeMesh::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {

	hit_record temp_rec;
	//just loop through all the faces
	//and calculate
	bool hit_anything = false;

	Vector origin = transform->applyTransform(r.origin(), true);
	Vector local_ray = transform->applyTransform(r.direction());

	

	return hit_anything;
}

Vector CubeMesh::getUVCoordinate(Vector hitPoint) const
{
	return Vector(0,0,0);
}

