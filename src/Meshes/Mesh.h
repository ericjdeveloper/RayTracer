#pragma once

#include "..\Vector.h"
#include "..\Transform.h"
#include "..\Ray.h"
#include "..\Materials\Material.h"

//struct for the collision data of an object
struct hit_record {
	float t;
	Vector p;
	Vector normal;
	Material *mat_ptr;
	float UV_x;
	float UV_y;
};

//Mesh class to handle rendering

class Mesh {
public:
	virtual bool hit(const ray&r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual void setTransform(Transform * tfm) { transform = tfm; }
	virtual Vector getUVCoordinate(Vector hitPoint) const {return Vector(0,0,0);};

protected:
	Transform *transform;
};
