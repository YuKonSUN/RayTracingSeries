#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
	ray() {}
	ray(const point3& _orign, const vec3& _direction) 
		: orig(_orign) , dir(_direction), tm(0.0) {}

	ray(const point3& _orign, const vec3& _direction, double time) 
		: orig(_orign) , dir(_direction), tm(time) {}

	point3 orign()const { return orig; }
	vec3 direction()const { return dir; }
	point3 at(double t)const {
		return orig + t * dir;
	}
	double time() const { return tm; }
private:
	point3 orig;
	vec3 dir;
	double tm;
};

#endif // !VEC_H
