#include "Material.h"

class Depth: public Material {
public:
	Depth(){}
	virtual bool scatter(const Ray& r_in, Vector& p, Vector& normal, float UV_x, float UV_y, Vector& attenuation, Ray& scattered) const {
		float dist = .05 * (p - r_in.origin()).squared_length();
        attenuation = Vector(1,1,1) * (dist / (dist+1));
		return false;

	}
	
};