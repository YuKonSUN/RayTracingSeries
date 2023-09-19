#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "vec3.h"

class metal : public material {
public:
	metal() {}
	metal(color _albeto, double _fuzz) : albeto(_albeto), fuzz(_fuzz){}
	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered)const override {
		auto reflection = reflect(r.direction(), rec.normal);
		scattered = ray(rec.p, reflection + fuzz * random_in_unit_sphere(), r.time());
		attenuation = albeto;
		return (dot(reflection, rec.normal) > 0);
	}

public:
	color albeto;
	double fuzz;
};

#endif
