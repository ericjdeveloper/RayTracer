#pragma once
#include "ray.h"

class material {
public:
	virtual bool scatter(const ray& r_in, vec3& p, vec3& normal, vec3& attenuation, ray& scattered) const = 0;

protected:
	inline vec3 random_in_unit_sphere() const {
		vec3 p;
		do {
			float randx = ((double)rand() / (RAND_MAX + 1));
			float randy = ((double)rand() / (RAND_MAX + 1));
			float randz = ((double)rand() / (RAND_MAX + 1));
			p = 2.0*vec3(randx, randy, randz) - vec3(1, 1, 1);

		} while (p.squared_length() >= 1);


		return p;
	}
};