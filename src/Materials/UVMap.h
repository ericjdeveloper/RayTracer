#pragma once

#include "Material.h"
#include "..\ScreenData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>


#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>

using std::cout; using std::cin;
using std::endl; using std::string;



using namespace std;

class UVMap : public Material {
public:

	ScreenData* texture;

	UVMap(string fname)
	{
		std::ifstream imgFile;
		imgFile.open(fname);

		string type;
		imgFile >>  type;

		int width, height;
		imgFile >> width;
		imgFile >> height;

		int colorDepth;
		imgFile >> colorDepth;


		texture = new ScreenData(width, height);
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{				

				int r,g,b;
				imgFile >> r;
				imgFile >> g;
				imgFile >> b;

				texture->setPixel(j, i, r, g, b);

			}
		}
	}

	bool scatter(const Ray& r_in, Vector& p, Vector& normal, float UV_x, float UV_y, Vector& attenuation, Ray& scattered) const {

		Vector target = p + normal + random_in_unit_sphere();
		scattered = Ray(p, target - p);
		
		// if(UV_x > 0.5f && UV_x < 0.75f)
		// 	std::cout << "wait";

		UV_x = min(max(0.0f, UV_x), 1.0f);
		UV_y = min(max(0.0f, UV_y), 1.0f);
		int x = floor(UV_x * texture->getWidth());
		int y = floor(UV_y * texture->getHeight());
		Uint8 r,g,b;
		texture->getPixel(x,y, r,g,b);

		float ir, ig, ib;
		ir = r / 255.0f;
		ig = g / 255.0f;
		ib = b / 255.0f;

		attenuation = Vector(ir, ig, ib);
		return true;

	}

	Vector albedo;


	
};