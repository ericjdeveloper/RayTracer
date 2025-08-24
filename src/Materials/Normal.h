#include "Material.h"

class Normal: public Material {
public:
	Normal(){}
	virtual bool scatter(const Ray& r_in, Vector& p, Vector& normal, float UV_x, float UV_y, Vector& attenuation, Ray& scattered) const {
		attenuation = normal;
		return false;

	}
	
};