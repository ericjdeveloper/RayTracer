#pragma once

#include "..\Vector.h"
#include "..\Transform.h"
#include "..\Fan.h"
#include "..\Materials\Material.h"

//struct for the collision data of an object
struct hit_record {
	float t;
	Vector p;
	Vector normal;
	Material *mat_ptr;
	Ray r;
	float UV_x;
	float UV_y;
};

//Mesh class to handle rendering

class Mesh {
public:
	virtual bool hit(const Fan& f, float tmin, float tmax, hit_record& rec) const =0;
	virtual void setTransform(Transform * tfm) { transform = tfm; }
	virtual Vector getUVCoordinate(Vector hitPoint) const {return Vector(0,0,0);};

protected:
	Transform *transform;
};
