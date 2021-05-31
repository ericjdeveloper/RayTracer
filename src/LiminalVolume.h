#pragma once

#include "Entity.h"
#include "Mesh.h"

class LiminalVolume : public Entity {
public:
	LiminalVolume(Vec3 pos, Mesh *m, Vec3 mult) : Entity(pos), mesh(m), spaceMultiplier(mult) { mesh->setTransform(&transform); };
	Vec3 spaceMultiplier;

	bool getHitDistance(const ray& r, float t_min, float t_max, hit_record& hitPos);

	Vec3 transformPoint(Vec3 point, int direction= 1);

private:
	Mesh *mesh;
};

bool LiminalVolume::getHitDistance(const ray& r, float t_min, float t_max, hit_record& t)
{
	return mesh->hit(r, t_min, t_max, t);

}

Vec3 LiminalVolume::transformPoint(Vec3 point, int direction)
{
	if (direction > 0)
		return point * spaceMultiplier;
	else
		return point / spaceMultiplier;
}
