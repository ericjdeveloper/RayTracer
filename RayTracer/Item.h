#pragma once

#include "Entity.h"
#include "Mesh.h";

//the item is a child of entity;
//it has some form of physical appearance
//represents the "normal" world objects
class Item : public Entity {
public:
	Item(vec3 pos, Mesh *m) : mesh(m), Entity(pos) {
		m->setTransform(&transform);
	};
	Mesh *mesh;
};