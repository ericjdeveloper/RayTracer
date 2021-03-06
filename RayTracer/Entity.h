#pragma once

#include "Transform.h"


//abstract class to represent all objects in the world
//(including cameras and lights)
class Entity {
public:
	//All entities exist at a position in space,
	//so they have a transform
	Transform transform;
};