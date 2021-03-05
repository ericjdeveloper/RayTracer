#pragma once
#include <math.h>

#include "hitable.h"
#include "material.h"

class cube : public hitable {
public:
	cube() {}
	cube(vec3 cen, float r, material *m) : center(cen), radius(r), mat(m) {};

	virtual bool hit(const ray& r, float tmin, float tmax, hyperspace *hs, hit_record& rec) const;
	vec3 center;
	float radius;
	material* mat;
};

bool bounds(float v, float min, float max)
{
	return (v > min && v < max);
}

bool cube::hit(const ray& r, float t_min, float t_max, hyperspace *hs, hit_record& rec) const {

	vec3* a = nullptr;
	vec3* b = nullptr;



	vec3 t_minX = r.point_at_parameter(((center.x() - radius) - r.origin().x()) / r.direction().x());
	vec3 t_maxX = r.point_at_parameter(((center.x() + radius) - r.origin().x()) / r.direction().x());

	vec3 t_minY = r.point_at_parameter(((center.y() - radius) - r.origin().y()) / r.direction().y());
	vec3 t_maxY = r.point_at_parameter(((center.y() + radius) - r.origin().y()) / r.direction().y());

	vec3 t_minZ = r.point_at_parameter(((center.z() - radius) - r.origin().z()) / r.direction().z());
	vec3 t_maxZ = r.point_at_parameter(((center.z() + radius) - r.origin().z()) / r.direction().z());
	
	if( bounds(t_minX.y(), center.y() - radius, center.y() + radius) &&
		bounds(t_minX.z(), center.z() - radius, center.z() + radius))
	{		
		if (a == nullptr)
			a = &t_minX;
		else
			b = &t_minX;
	}

	if (bounds(t_maxX.y(), center.y() - radius, center.y() + radius) &&
		bounds(t_maxX.z(), center.z() - radius, center.z() + radius))
	{
		if (a == nullptr)
			a = &t_minX;
		else
			b = &t_minX;
	}



	if (bounds(t_minY.x(), center.x() - radius, center.x() + radius) &&
		bounds(t_minY.z(), center.z() - radius, center.z() + radius))
	{
		if (a == nullptr)
			a = &t_minY;
		else
			b = &t_minY;
	}

	if (bounds(t_maxY.x(), center.x() - radius, center.x() + radius) &&
		bounds(t_maxY.z(), center.z() - radius, center.z() + radius))
	{
		if (a == nullptr)
			a = &t_minY;
		else
			b = &t_minY;
	}

	if (bounds(t_minZ.x(), center.x() - radius, center.x() + radius) &&
		bounds(t_minZ.y(), center.y() - radius, center.y() + radius))
	{
		if (a == nullptr)
			a = &t_minZ;
		else
			b = &t_minZ;
	}

	if (bounds(t_maxZ.x(), center.x() - radius, center.x() + radius) &&
		bounds(t_maxZ.y(), center.y() - radius, center.y() + radius))
	{
		if (a == nullptr)
			a = &t_minZ;
		else
			b = &t_minZ;
	}

	if (a != nullptr) {
		if (b != nullptr && (*b - r.origin()).length() < (*a - r.origin()).length())
		{

			rec.p = *b;
			rec.t = (*b - r.origin()).length();
			

		}
		else
		{

			rec.p = *a;
			rec.t = (*a - r.origin()).length();
		}

		rec.mat_ptr = mat;
		vec3 relative = rec.p - center;
		if (abs(relative.x()) > abs(relative.y()) && abs(relative.x()) > abs(relative.z()))
		{
			rec.normal = vec3(relative.x() / abs(relative.x()), 0, 0);
		}
		else if (abs(relative.y()) > abs(relative.x()) && abs(relative.y()) > abs(relative.z()))
		{
			rec.normal = vec3(0, relative.y() / abs(relative.z()), 0);
		}
		else
		{
			rec.normal = vec3(0, 0, relative.z() / abs(relative.z()));
		}

		return true;
	}
		


	return false;
}

