#pragma once

#include "Material.h"


class Lambertian : public Material {
public:
	Lambertian(const Vector& a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, Vector& p, Vector& normal, float UV_x, float UV_y, Vector& attenuation, Ray& scattered) const {

		Vector target = p + normal + random_in_unit_sphere();
		scattered = Ray(p, target - p);
		attenuation = albedo;
		return true;

	}

	Vector albedo;


	
};