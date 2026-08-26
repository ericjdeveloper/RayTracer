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

	bool hit(const Fan& f, float tmin, float tmax, hit_record& rec) const;
	Vector getUVCoordinate(Vector hitPoint) const;
	Vector center;
	float size;
};

//cube override
bool CubeMesh::hit(const Fan& f, float t_min, float t_max, hit_record& rec) const {

	//just loop through all the faces
	//and calculate
	Vector origin = f.origin(); //transform->applyTransform(r.origin(), true);
	Vector forward = f.direction();//transform->applyTransform(r.direction());
	Ray r = Ray(origin, forward);

	hit_record h = hit_record();
	h.t = -1;
	rec.t = -1;

	float bound = (size / 2);
	
	float hits[6];

	hits[0] = forward.y()? (center.y() + bound - origin.y()) / forward.y() : -1;
	hits[1] = forward.y()? (center.y() - bound - origin.y()) / forward.y() : -1;
	
	hits[2] = forward.x()? (center.x() + bound - origin.x()) / forward.x() : -1;
	hits[3] = forward.x()? (center.x() - bound - origin.x()) / forward.x() : -1;
	
	hits[4] = forward.z()? (center.z() + bound - origin.z()) / forward.z() : -1;
	hits[5] = forward.z()? (center.z() - bound - origin.z()) / forward.z() : -1;

	Vector normals[8] = {
		Vector(0,1,0),
		Vector(0,-1,0),
		Vector(1,0,0),
		Vector(-1,0,0),
		Vector(0,0,1),
		Vector(0,0,-1),
		Vector(0,0,0,1),
		Vector(0,0,0,-1)
	};

	for(int i=0;i<8;i++)
	{
		if (hits[i] < 0) continue;
		
		if (h.t == -1 || hits[i] < h.t)
		{
			Vector norm = normals[i];
			Vector point = r.point_at_parameter(hits[i]);
			Vector diff = point - center;
			diff -= diff * norm * norm;
			if(	abs(diff.w()) <= bound
				&& abs(diff.x()) <= bound
				&& abs(diff.y()) <= bound
				&& abs(diff.z()) <= bound
			){
				h.t = hits[i];
				h.p = point;
				h.normal = norm;
			}
		}
	}


	// float dist = min(m_y_upper, min(m_y_lower, min(m_x_upper, min(m_x_lower, min(m_z_upper, m_z_lower)))));
	if (h.t <= t_min || h.t >= t_max) return false;

	rec.t = h.t;
	rec.p = h.p;
	rec.normal = h.normal;

	//fancy but probably slow way to get other two axes
	//(can't just use cross as we need to have a proper "up" vector)
	int axis_up = abs(rec.normal.x() + rec.normal.z()) ? 1 : 2;
	int axis_left = abs(rec.normal.y() + rec.normal.z()) ? 0 : 2;
	
	// uv calculation
	float plane_x = (rec.p[axis_up]);
	float plane_y = (rec.p[axis_left]);
	rec.UV_x = (plane_x / size) + 0.5f;
	rec.UV_y = (plane_y / size) + 0.5f;
	return true;
}

Vector CubeMesh::getUVCoordinate(Vector hitPoint) const
{
	return Vector(0,0,0);
}

