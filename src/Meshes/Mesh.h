#pragma once

#include "Vector.h"
#include "Transform.h"
#include "Ray.h"
#include "Materials\Material.h"

//struct for the collision data of an object
struct hit_record {
	float t;
	Vector p;
	Vector normal;
	Material *mat_ptr;
};

//Mesh class to handle rendering

class Mesh {
public:
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual void setTransform(Transform * tfm) { transform = tfm; }

protected:
	Transform *transform;
};
