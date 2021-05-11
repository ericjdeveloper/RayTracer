#pragma once

#include "Material.h"

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n)*n;
}


class Metal : public Material {
public:
	Metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1;}

	virtual bool scatter(const ray& r_in, vec3& p, vec3& normal, vec3& attenuation, ray& scattered) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), normal);
		scattered = ray(p, reflected + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), normal) > 0);

	}

	vec3 albedo;
	float fuzz;
};