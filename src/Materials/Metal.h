#pragma once

#include "Material.h"

Vec3 reflect(const Vec3& v, const Vec3& n)
{
	return v - 2 * dot(v, n)*n;
}


class Metal : public Material {
public:
	Metal(const Vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1;}

	virtual bool scatter(const ray& r_in, Vec3& p, Vec3& normal, Vec3& attenuation, ray& scattered) const {
		Vec3 reflected = reflect(unit_vector(r_in.direction()), normal);
		scattered = ray(p, reflected + fuzz*random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), normal) > 0);

	}

	Vec3 albedo;
	float fuzz;
};