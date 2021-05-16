#pragma once

#include "Material.h"


class Lambertian : public Material {
public:
	Lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, vec3& p, vec3& normal, vec3& attenuation, ray& scattered) const {

		vec3 target = p + normal + random_in_unit_sphere();
		scattered = ray(p, target - p);
		attenuation = albedo;
		return true;

	}

	vec3 albedo;


	
};