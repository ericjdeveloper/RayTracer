#pragma once

#include "Vector.h"
#include "Ray.h"

class Fan
{
public:
	// creates a ray, but as a growing plane. 
	// i.e. imagine a bac triangle that extends infinitely
	Fan() {}
	Fan(const Vector &a, const Vector& b, Vector axis, int angle) {
		A = a;
		B = b;
		Axis = axis;
		Angle = angle;
	}
	Vector origin() const { return A; }
	Vector direction() const { return B; }
	//Vector point_at_parameter(float t) const { return A + t * B; }

	Vector A;
	Vector B;
	Vector Axis;
	float Angle;
};