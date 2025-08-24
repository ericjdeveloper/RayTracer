#pragma once

#include "Material.h"


class Luminous : public Material {
public:
	Luminous(const Vector& a) : albedo(a) {}
	virtual bool scatter(const Ray& r_in, Vector& p, Vector& normal, float UV_x, float UV_y, Vector& attenuation, Ray& scattered) const {
		attenuation = albedo;
		return false;

	}
	Vector albedo;
	
};