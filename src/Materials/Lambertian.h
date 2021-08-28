#pragma once

#include "Material.h"


class Lambertian : public Material {
public:
	Lambertian(const Vector& a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, Vector& p, Vector& normal, Vector& attenuation, ray& scattered) const {

		Vector target = p + normal + random_in_unit_sphere();
		scattered = ray(p, target - p);
		attenuation = albedo;
		return true;

	}

	Vector albedo;


	
};