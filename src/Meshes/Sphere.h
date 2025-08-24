#pragma once

#include "Mesh.h"


//Sphere mesh handler
class SphereMesh : public Mesh {
public:
	//initializer that sets center, radius, and material
	SphereMesh(float d=1, Vector cen = Vector(0,0,0,0)) : center(cen), diameter(d) {};

	//override for the hit call
	bool hit(const Ray& r, float tmin, float tmax, hit_record& rec) const;

	Vector getUVCoordinate(Vector hitPoint) const;

	//data for center, radius, and material;
	Vector center;
	float diameter;
};

//override of hit function for the sphere
bool SphereMesh::hit(const Ray& r, float t_min, float t_max, hit_record& rec) const {

	//the reasoning for the math is based on the "Ray Tracing In a Weekend" article,
	//but the quick explanation is that the intersection of a line can be determined by
	//the quadratic equation. 
	
	Vector globalCenter = transform->applyTransform(center, true);
	float radius = diameter / 2;
	float scaledRadius = radius; // transform->scale.length();

	Vector oc = r.origin() - globalCenter;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - (scaledRadius * scaledRadius);
	float discriminant = b * b -  a * c;

	//If the descriminant has 2 roots its real, otherwise the 
	//line does not exist
	if (discriminant > 0)
	{
		//option a for the quadratic equation
		float temp = (-b - sqrt(b*b - a * c)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - globalCenter) / scaledRadius;
			Vector uv = getUVCoordinate(rec.p);
			rec.UV_x = uv.x();
			rec.UV_y = uv.y();
			return true;
		}

		//option 2 for the quadratic equation
		temp = (-b + sqrt(b*b - a * c)) / a;
		if (temp < t_max && temp > t_min) {
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (rec.p - globalCenter) / scaledRadius;
			Vector uv = getUVCoordinate(rec.p);
			rec.UV_x = uv.x();
			rec.UV_y = uv.y();
			return true;
		}
	}
	
	return false;
}

Vector SphereMesh::getUVCoordinate(Vector hitPoint) const
{
		Vector localized = hitPoint - center;
		Vector right = transform->applyTransform(Vector(-1,0,0) * diameter);
		Vector down = transform->applyTransform(Vector(0,-1,0) * diameter);
		float Angle = acos(dot(localized, right)) / 2;
		return Vector(Angle, dot(localized, down) + 0.5f,0);
}