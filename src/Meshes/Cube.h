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

	bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;
	Vector getUVCoordinate(Vector hitPoint) const;
	Vector center;
	float size;
};

//cube override
bool CubeMesh::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {

	//just loop through all the faces
	//and calculate
	Vector origin = r.origin(); //transform->applyTransform(r.origin(), true);
	Vector local_ray = r.direction();//transform->applyTransform(r.direction());

	hit_record h = hit_record();
	h.t = -1;
	rec.t = -1;

	float bound = (size / 2);
	
	float hits[6];

	hits[0] = local_ray.y()? (center.y() + bound - origin.y()) / local_ray.y() : -1;
	hits[1] = local_ray.y()? (center.y() - bound - origin.y()) / local_ray.y() : -1;
	
	hits[2] = local_ray.x()? (center.x() + bound - origin.x()) / local_ray.x() : -1;
	hits[3] = local_ray.x()? (center.x() - bound - origin.x()) / local_ray.x() : -1;
	
	hits[4] = local_ray.z()? (center.z() + bound - origin.z()) / local_ray.z() : -1;
	hits[5] = local_ray.z()? (center.z() - bound - origin.z()) / local_ray.z() : -1;

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
	
	// uv calculation
	float plane_x = rec.p.x();
	float plane_y = rec.p.y();
	rec.UV_x = (plane_x / size) + 0.5f;
	rec.UV_y = (plane_y / size) + 0.5f;
	return true;
}

Vector CubeMesh::getUVCoordinate(Vector hitPoint) const
{
	return Vector(0,0,0);
}

