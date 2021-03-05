#pragma once

#include "vec3.h"

class hyperspace {
public:
	virtual vec3 get_point(const vec3& v_in) const = 0;
};