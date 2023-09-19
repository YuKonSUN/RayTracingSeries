#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"

class Sphere : public hittable {
public:
	Sphere() {}
	Sphere(const point3& _center, double _radius, shared_ptr<material> _mat_ptr) 
		: center1(_center), radius(_radius), mat_ptr(_mat_ptr), isMoving(false) {
		auto rvec = vec3(_radius, _radius, _radius);
		bbox = aabb(_center - rvec, _center + rvec);
	}

	Sphere(const point3& _center1, const point3& _center2, double _radius, shared_ptr<material> _mat_ptr) 
		: center1(_center1), center2(_center2), radius(_radius), mat_ptr(_mat_ptr), isMoving(true) 
	{
		auto rvec = vec3(radius, radius, radius);
		aabb box1 = aabb(_center1 - rvec, _center1 + rvec);
		aabb box2 = aabb(_center2 - rvec, _center2 + rvec);
		bbox = aabb(box1, box2);
		center_vec = _center2 - _center1;
	}

	aabb bounding_box() const { return bbox; }
	virtual bool hit(
		const ray& r, interval ray_t, hit_record& record) const override;

private:
	point3 center1;
	point3 center2;
	vec3 center_vec;
	bool isMoving;
	double radius;
	shared_ptr<material> mat_ptr;
	aabb bbox;

	point3 center(double time) const
	{
		return center1 + time * center_vec;
	}

	static void get_sphere_uv(const point3& p, double& u, double& v) {
		auto theta = acos(-p.y());
		auto phi = atan2(-p.z(), p.x()) + pi;

		u = phi / (2 * pi);
		v = theta / pi;
	}
};

bool Sphere::hit(const ray& r, interval ray_t, hit_record& record) const {
	point3 _center = isMoving ? center(r.time()) : center1;
	auto oc = r.orign() - _center;
	auto a = dot(r.direction(), r.direction());
	auto half_b = dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	double discriminat = half_b * half_b - a * c;

	if (discriminat < 0)
		return false;
	double sqrtd = sqrt(discriminat);
	double t = (-half_b - sqrtd) / a;
	if (!ray_t.surrounds(t)) {
		t = (-half_b + sqrtd) / a;
		if (!ray_t.surrounds(t))
			return false;
	}
	record.t = t;
	record.p = r.at(t);
	auto outward_normal = (record.p - _center) / radius;
	record.set_normal(r, outward_normal);
	get_sphere_uv(outward_normal, record.u, record.v);
	record.mat_ptr = mat_ptr;

	return true;
}

//bool Sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
//	vec3 oc = r.orign() - center;
//	auto a = r.direction().length_squared();
//	auto half_b = dot(oc, r.direction());
//	auto c = oc.length_squared() - radius * radius;
//
//	auto discriminant = half_b * half_b - a * c;
//	if (discriminant < 0) return false;
//	auto sqrtd = sqrt(discriminant);
//
//	// Find the nearest root that lies in the acceptable range.
//	auto root = (-half_b - sqrtd) / a;
//	if (root < t_min || t_max < root) {
//		root = (-half_b + sqrtd) / a;
//		if (root < t_min || t_max < root)
//			return false;
//	}
//
//	rec.t = root;
//	rec.p = r.at(rec.t);
//	rec.normal = (rec.p - center) / radius;
//
//	return true;
//}

#endif // !SPHERE_H
