#pragma once

#include "Vec3.h"
#include "Item.h"

class WorldSpace {

public:
	virtual bool getColor(const ray& r, Item **wrld_obs, int itm_cnt, int depth, vec3& color) = 0;
};