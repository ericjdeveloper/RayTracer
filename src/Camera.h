#pragma once

#include "Entity.h"
#include "Ray.h"

//Camera handles in-world aspect of the rendering
class Camera : public Entity {
public:
	//constructor sets the viewport plane size,
	//samples count
	//and max_bounces
	Camera(Vector pos): Entity(pos) {
		viewport_plane = Vector(4.0, 2.0, 2.0);
		samples = 50;
		max_bounces = 10;
	}
	
	//returns the ray at a given point on the viewport plane
	//(0-1 on each dimension)
	ray get_ray(float u, float v) { 
		return ray(transform.position,
					unit_vector(transform.applyTransform(
						Vector(-viewport_plane.x() /2, -viewport_plane.y() /2, viewport_plane.z(), viewport_plane.w()) + 
						Vector(viewport_plane.x() * u,viewport_plane.y() * v)
						)
					)
				);
	}

	//the plane width, height, and distance from origin
	//that represents the 2d area the that is rendered
	Vector viewport_plane;
	//the number of samples to render from this camera
	int samples;
	//the maximum number of light bounces this camera should render
	int max_bounces;
};