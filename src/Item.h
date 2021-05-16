#pragma once

#include "Entity.h"
#include "Meshes\\Mesh.h"
#include "Materials\\Material.h"

//the item is a child of entity;
//it has some form of physical appearance
//represents the "normal" world objects
class Item : public Entity {
public:
	Item(vec3 pos, Mesh *m, Material *mat) : mesh(m), Entity(pos), material(mat) {
		m->setTransform(&transform);
	};

	bool hit(const ray& r, float t_min, float t_max, hit_record& rec);

	Material *material;
	Mesh *mesh;
};

bool Item::hit(const ray& r, float t_min, float t_max, hit_record& rec)
{
	
	bool isHit = mesh->hit(r, t_min, t_max, rec);
	rec.mat_ptr = material;
	return isHit;
}