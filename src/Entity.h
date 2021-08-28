#pragma once

#include "Transform.h"


//abstract class to represent all objects in the world
//(including cameras and lights)
class Entity {
public:
	Entity(Vector pos) { transform.position = pos; }
	//All entities exist at a position in space,
	//so they have a transform
	Transform transform;
};