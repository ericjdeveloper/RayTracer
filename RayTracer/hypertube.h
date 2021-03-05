#pragma once
#include "hyperspace.h"

class hypertube : public hyperspace {
public:
	virtual vec3 get_point(const vec3& v_in) const {

		if (   v_in.e[0] >= 1 && v_in.e[0] <= 2
			&& v_in.e[1] >= 0 && v_in.e[1] <= 1
			&& v_in.e[2] >= -3 && v_in.e[2] <= -1)
		{
			vec3 transformed = vec3(
									0,0,0//(v_in.e[0] - 1) / 2 + 1,
									//(v_in.e[1]) / 2,
									//(v_in.e[2] + 1) / 2 + 1
									);
			return transformed;
		}

		return v_in;

	}
};