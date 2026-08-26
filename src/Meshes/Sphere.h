#pragma once

#include "Mesh.h"


//Sphere mesh handler
class SphereMesh : public Mesh {
public:
	//initializer that sets center, radius, and material
	SphereMesh(float d=1, Vector cen = Vector(0,0,0,0)) : center(cen), diameter(d) {};

	//override for the hit call
	bool hit(const Fan& f, float tmin, float tmax, hit_record& rec) const;

	Vector getUVCoordinate(Vector hitPoint) const;

	//data for center, radius, and material;
	Vector center;
	float diameter;
};

//override of hit function for the sphere
bool SphereMesh::hit(const Fan& f, float t_min, float t_max, hit_record& rec) const {

	// take the cross product of the fan
	// find the intersection with cross going through hypersphere origin

	Vector sphere_v = center - f.origin();
	Vector perp = sphere_v - dot(sphere_v, f.direction()) * f.direction() - dot(sphere_v, f.Axis) * f.Axis;
	float t = perp.length();
	float radius = diameter / 2;
	if (t > radius)
		return false;

	
	float remaining_radius = sqrt(radius * radius - t * t);
	
	Vector origin_to_center = sphere_v - perp;
	Vector norm = unit_vector(origin_to_center);
	float d = dot(norm, f.direction());
	if (d < 0)
		return false;

	float threshold = cos(f.Angle * DEG2RAD);
	if (d > threshold)
	{
		rec.t = sqrt(origin_to_center.squared_length() - remaining_radius * remaining_radius);
		rec.r = Ray(f.origin(), norm);
		rec.p = f.origin() + rec.t * norm;
		rec.normal = unit_vector(rec.p - center);
		// Vector uv = getUVCoordinate(rec.p);
		rec.UV_x = 0; //uv.x();
		rec.UV_y = 0; //uv.y();
		return true;
	}

	Vector edge = f.direction() * cos(f.Angle * DEG2RAD) + f.Axis * sin(f.Angle * DEG2RAD);
	float dist = dot(origin_to_center, edge);
	Vector p = dist * edge;
	float mag_to_center = (origin_to_center - p).length();
	if (mag_to_center > remaining_radius)
		return false;

	float radius_last_2 = remaining_radius * remaining_radius - mag_to_center* mag_to_center;
	rec.t = dist - sqrt(radius_last_2);
	rec.r = Ray(f.origin(), edge);
	rec.p = rec.r.point_at_parameter(rec.t);
	rec.normal = unit_vector(rec.p - center);
	// Vector uv = getUVCoordinate(rec.p);
	rec.UV_x = 0; //uv.x();
	rec.UV_y = 0; //uv.y();
	return true;

	// if (d > dot(f.C, f.direction()))
	// {
	// 	return false;
	// }
	
	// Vector axis_3 = cross(perp, f.direction());
	// float d = dot(center_on_plane - f.origin(), f.direction());
	// float v = d * dot(f.C - f.A, f.direction());
	
	// float center_a3 = dot(axis_3, f.origin() - center_on_plane);
	// float bound_a3 = dot(axis_3, f.origin() - v * (f.C - f.A).make_unit_vector());
	
	// if (abs(center_a3) - remaining_radius > abs(bound_a3))
	// 	return false;
	
	// float actual_a3 = max(abs(center_a3) - remaining_radius, abs(bound_a3));
	// float actual_a2 = sqrt(remaining_radius * remaining_radius - actual_a3 * actual_a3);
	
	// Vector final_point = center_on_plane - axis_3 * actual_a3 - f.direction() * actual_a2;
	// float tfinal = dot(final_point, f.A);
		

	}

Vector SphereMesh::getUVCoordinate(Vector hitPoint) const
{
		Vector localized = hitPoint - center;
		Vector right = transform->applyTransform(Vector(-1,0,0) * diameter);
		Vector down = transform->applyTransform(Vector(0,-1,0) * diameter);
		float Angle = acos(dot(localized, right)) / 2;
		return Vector(Angle, dot(localized, down) + 0.5f,0);
}