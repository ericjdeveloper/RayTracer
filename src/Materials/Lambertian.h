#pragma once

#include "Material.h"


class Lambertian : public Material {
public:
	Lambertian(const Vec3& a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, Vec3& p, Vec3& normal, Vec3& attenuation, ray& scattered) const {

		Vec3 target = p + normal + random_in_unit_sphere();
		scattered = ray(p, target - p);
		attenuation = albedo;
		return true;

	}

	Vec3 albedo;


	
};