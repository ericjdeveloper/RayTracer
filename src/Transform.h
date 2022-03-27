#pragma once

#include "Vector.h"
#define DEG2RAD M_PI/180.0
#define RAD2DEG 180.0/M_PI


//the transform class handles the postion, rotation and scale of the object
class Transform {
public:
	Vector position;
	Vector rotation[2] = {
		Vector(0,0,0),
		Vector(0,0,0) // xy, xz, yz
		};
	Vector scale = Vector(1,1,1,1);

	Vector applyTransform(Vector inV, bool isPosition);
};

Vector Transform::applyTransform(Vector inV, bool isPosition = false)
{

	//convert rotation into radians
	float r_x = rotation[0].x() * DEG2RAD;
	float r_y = rotation[0].y() * DEG2RAD;
	float r_z = rotation[0].z() * DEG2RAD;

	float r_xw = rotation[1].x() * DEG2RAD;
	float r_yw = rotation[1].y() * DEG2RAD;
	float r_zw = rotation[1].z() * DEG2RAD;

	//get initial values
	float x = inV.x() * scale.x();
	float y = inV.y() * scale.y();
	float z = inV.z() * scale.z();
	float w = inV.w() * scale.w();
	
	//apply zw rotation
	float x_zw = x * cos(r_z) - y * sin(r_z);
	float y_zw = x * sin(r_z) + y * cos(r_z);
	float z_zw = z;
	float w_zw = w;

	//apply yw rotation
	float x_yw = x_zw * cos(r_y) - z_zw * sin(r_y);
	float y_yw = y_zw;
	float z_yw = x_zw * sin(r_y) + z_zw * cos(r_y);
	float w_yw = w_zw;

	//apply yz rotation
	float x_yz = x_yw * cos(r_xw) - w_yw * sin(r_xw);
	float y_yz = y_yw;
	float z_yz = z_yw;
	float w_yz = x_yw * sin(r_xw) + w_yw * cos(r_xw);

	//apply xw rotation
	float x_xw = x_yz;
	float y_xw = y_yz * cos(r_x) - z_yz * sin(r_x);
	float z_xw = y_yz * sin(r_x) + z_yz * cos(r_x);
	float w_xw = w_yz;

	//apply xz rotation
	float x_xz = x_xw;
	float y_xz = y_xw * cos(r_yw) - w_xw * sin(r_yw);
	float z_xz = z_xw;
	float w_xz = y_xw * sin(r_yw) + w_xw * cos(r_yw);

	//apply xy rotation
	float x_xy = x_xz;
	float y_xy = y_xz;
	float z_xy = z_xz * cos(r_zw) - w_xz * sin(r_zw);
	float w_xy = z_xz * sin(r_zw) + w_xz * cos(r_zw);

	//https://math.stackexchange.com/questions/1402362/rotation-in-4d

	//apply the transformation
	Vector transformed = Vector(x_xy, y_xy, z_xy, w_xy);

	//return rotated vector
	if (isPosition)
	{
		transformed += position;
	}
	return transformed;
}