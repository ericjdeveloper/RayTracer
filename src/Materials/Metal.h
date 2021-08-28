#pragma once

#include "Material.h"

Vector reflect(const Vector& v, const Vector& n)
{
	return v - 2 * dot(v, n)*n;
}


class Metal : public Material {
public:
	Metal(const Vector& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1;}

	virtual bool scatter(const ray& r_in, Vector& p, Vector& normal, Vector& attenuation, ray& scattered) const {
		Vector reflected = reflect(unit_vector(r_in.direction()), normal);
		scattered = ray(p, reflected + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), normal) > 0);

	}

	Vector albedo;
	float fuzz;
};