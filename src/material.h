#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "texture.h"

struct hit_record;

class material {
public:
	virtual bool scatter(const ray& r, const hit_record& rec, color& attenuation, ray& scattered)const = 0;

	virtual color emitted(double u, double v, const point3& p) const {
		return color(0, 0, 0);
	}
};

class dielectric : public material {
public:
	dielectric(double _ir) : ir(_ir) {}
	virtual bool scatter(
		const ray& r, const hit_record& rec, color& attenuation, ray& scattered
	)const override {
		auto refraction_ratio = rec.front_face ? (1.0 / ir) : ir;
		attenuation = color(1.0, 1.0, 1.0);
		vec3 unit_direction = unit_vector(r.direction());
		double cos_theta = fmin(dot(-unit_direction, rec.normal), 1);
		double sin_theta = sqrt(1 - cos_theta * cos_theta);

		bool cannot_refract = sin_theta * refraction_ratio > 1.0;
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
		{
			direction = reflect(unit_direction, rec.normal);
		}
		else
		{
			direction = refact(unit_vector(r.direction()), rec.normal, refraction_ratio);
		}
		scattered = ray(rec.p, direction, r.time());
		return true;
	}
public:
	double ir; // Index of refraction

private:
	static double reflectance(double cosine, double ref_idx)
	{
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 *= r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};

class diffuse_light : public material {
public:
	diffuse_light(shared_ptr<texture> a) : emit(a) {}
	diffuse_light(color c) : emit(make_shared<solid_color>(c)) {}
	bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered) const override
	{
		return false;
	}
	color emitted(double u, double v, const point3& p) const override {
		return emit->value(u, v, p);
	}

private:
	shared_ptr<texture> emit;
};

class isotropic : public material {
public:
	isotropic(color c) : albedo(make_shared<solid_color>(c)) {}
	isotropic(shared_ptr<texture> a) : albedo(a) {};

	bool scatter(const ray& r_in, const hit_record& rec, color& attentuation, ray& scattered) const override
	{
		scattered = ray(rec.p, random_unit_vecotr(), r_in.time());
		attentuation = albedo->value(rec.u, rec.v, rec.p);
		return true;
	}

private:
	shared_ptr<texture> albedo;
};

#endif
