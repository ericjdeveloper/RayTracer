#pragma once

#include "Vector.h"

class ray
{
public:
	ray() {}
	ray(const Vector &a, const Vector& b) { A = a; B = b; }
	Vector origin() const { return A; }
	Vector direction() const { return B; }
	Vector point_at_parameter(float t) const { return A + t * B; }

	Vector A;
	Vector B;
};