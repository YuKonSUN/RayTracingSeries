#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "vec3.h"
#include "texture.h"

class lambertian : public material {
public:
	lambertian() {}
	lambertian(const color& a) : albeto(make_shared<solid_color>(a)) {}
	lambertian(shared_ptr<texture> a) : albeto(a) {}
	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered)const override{
		vec3 scatter_dir = rec.normal + random_unit_vecotr();
		if (scatter_dir.near_zero()) {
			scatter_dir = rec.normal;
		}
		scattered = ray(rec.p, scatter_dir, r.time());
		attenuation = albeto->value(rec.u, rec.v, rec.p);
		return true;
	}

private:
	shared_ptr<texture> albeto;
};

#endif // !LAMBERTIAN_H
