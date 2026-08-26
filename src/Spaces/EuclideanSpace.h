#pragma once

#include "WorldSpace.h"


class EuclideanSpace : public WorldSpace {
private:
	bool getHit(const Fan& f, Item *wrld_obs, float min_dist, float max_dist, hit_record& rec);
};

bool EuclideanSpace::getHit(const Fan& f, Item *wrld_obs, float min_dist, float max_dist, hit_record& rec)
{
	return wrld_obs->hit(f, min_dist, max_dist, rec);
}