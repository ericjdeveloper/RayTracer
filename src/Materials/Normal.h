#include "Material.h"

class Normal: public Material {
public:
	Normal(){}
	virtual bool scatter(const ray& r_in, Vector& p, Vector& normal, float UV_x, float UV_y, Vector& attenuation, ray& scattered) const {
		attenuation = normal;
		return false;

	}
	
};