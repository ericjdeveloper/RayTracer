#pragma once
#include "..\Ray.h"
class Material {
public:
	virtual bool scatter(const Ray& r_in, Vector& p, Vector& normal, float UV_x, float UV_y, Vector& attenuation, Ray& scattered) const = 0;

protected:
	inline Vector random_in_unit_sphere() const {
		Vector p;
		do {
			float randx = ((double)rand() / (RAND_MAX + 1));
			float randy = ((double)rand() / (RAND_MAX + 1));
			float randz = ((double)rand() / (RAND_MAX + 1));
			float randw = ((double)rand() / (RAND_MAX + 1));
			p = 2.0*Vector(randx, randy, randz, randw) - Vector(1, 1, 1,1);

		} while (p.squared_length() >= 1);


		return p;
	}
};