#pragma once

#include "vec3.h"

//the transform class handles the postion, rotation and scale of the object
class Transform {
public:
	vec3 position;
	vec3 rotation;
	vec3 scale;
};