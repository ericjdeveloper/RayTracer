#pragma once

#include "LiminalVolume.h"

class LiminalWorld{
public:
	LiminalVolume **volumes;
	int volumeCount = 0;


	bool volumeHit(const ray& r, float& t, vec3& nextDirection);


	void addVolume(LiminalVolume* vol);

};

void LiminalWorld::addVolume(LiminalVolume* vol)
{

	LiminalVolume **new_obs = new LiminalVolume *[volumeCount + 1];


	for (int i = 0; i < volumeCount; ++i)
	{
		new_obs[i] = volumes[i];
	}


	new_obs[volumeCount++] = vol;


	volumes = new_obs;
}

bool LiminalWorld::volumeHit(const ray& r, float& t, vec3& skewed)
{


	t = FLT_MAX;
	bool hitFlag = false;

	for (int i = 0; i < volumeCount; i++)
	{
		hit_record temp;
		if (volumes[i]->getHitDistance(r, 0, t, temp)) {
			hitFlag = true;
			t = temp.t;


			
			int dir = (dot(unit_vector(r.direction()), unit_vector(temp.normal)) < 0) ? -1 : 1;

			skewed = volumes[i]->transformPoint(r.direction(), dir);
		}
	}

	return hitFlag;
}