#pragma once

#include "WorldSpace.h"


class EuclideanSpace : public WorldSpace {
private:
	bool getHit(const ray& r, Item *wrld_obs, float min_dist, float max_dist, hit_record& rec);
};

bool EuclideanSpace::getHit(const ray& r, Item *wrld_obs, float min_dist, float max_dist, hit_record& rec)
{
	return wrld_obs->hit(r, min_dist, max_dist, rec);
}