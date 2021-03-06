#pragma once

#include "Entity.h"
#include "Mesh.h";

//the item is a child of entity;
//it has some form of physical appearance
//represents the "normal" world objects
class Item : public Entity {
public:
	Item(Mesh *m) : mesh(m) {};
	Mesh *mesh;
};