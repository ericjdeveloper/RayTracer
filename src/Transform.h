#pragma once

#include "Vec3.h"
#define DEG2RAD M_PI/180.0
#define RAD2DEG 180.0/M_PI


//the transform class handles the postion, rotation and scale of the object
class Transform {
public:
	Vec3 position;
	Vec3 rotation;
	Vec3 scale = Vec3(1,1,1);

	Vec3 applyTransform(Vec3 inV, bool isPosition);
};

Vec3 Transform::applyTransform(Vec3 inV, bool isPosition = false)
{

	//convert rotation into radians
	float r_x = rotation.x() * DEG2RAD;
	float r_y = rotation.y() * DEG2RAD;
	float r_z = rotation.z() * DEG2RAD;

	//get initial values
	float x = inV.x() * scale.x();
	float y = inV.y() * scale.y();
	float z = inV.z() * scale.z();
	
	//apply x rotation
	float x_x = x;
	float y_x = y * cos(r_x) - z * sin(r_x);
	float z_x = y * sin(r_x) + z * cos(r_x);

	//apply y rotation
	float x_xy = x_x * cos(r_y) + z_x * sin(r_y);
	float y_xy = y_x;
	float z_xy = -x_x * sin(r_y) + z_x * cos(r_y);

	//apply z rotation
	float x_xyz = x_xy * cos(r_z) - y_xy * sin(r_z);
	float y_xyz = x_xy * sin(r_z) + y_xy * cos(r_z);
	float z_xyz = z_xy;

	//apply the transformation
	Vec3 transformed = Vec3(x_xyz, y_xyz, z_xyz);

	//return rotated vector
	if (isPosition)
	{
		transformed += position;
	}
	return transformed;
}