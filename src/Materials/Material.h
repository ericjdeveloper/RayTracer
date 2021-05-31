#pragma once
#include "ray.h"

class Material {
public:
	virtual bool scatter(const ray& r_in, Vec3& p, Vec3& normal, Vec3& attenuation, ray& scattered) const = 0;

protected:
	inline Vec3 random_in_unit_sphere() const {
		Vec3 p;
		do {
			float randx = ((double)rand() / (RAND_MAX + 1));
			float randy = ((double)rand() / (RAND_MAX + 1));
			float randz = ((double)rand() / (RAND_MAX + 1));
			p = 2.0*Vec3(randx, randy, randz) - Vec3(1, 1, 1);

		} while (p.squared_length() >= 1);


		return p;
	}
};