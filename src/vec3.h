#ifndef VEC_H
#define VEC_H

#include <iostream>
#include "rtweekend.h"

using std::sqrt;

class vec3 {
public:
	vec3() : e{ 0, 0, 0 } {};
	vec3(double x, double y, double z) : e{ x, y, z } {};

	double x() const { return e[0]; };
	double y() const { return e[1]; };
	double z() const { return e[2]; };

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& other) {
		e[0] += other.e[0];
		e[1] += other.e[1];
		e[2] += other.e[2];
		return *this;
	}
	vec3& operator-=(const vec3& other) {
		e[0] -= other.e[0];
		e[1] -= other.e[1];
		e[2] -= other.e[2];
		return *this;
	}
	vec3& operator*=(const double x) {
		e[0] *= x;
		e[1] *= x;
		e[2] *= x;
		return *this;
	}
	vec3& operator/=(const double x) {
		return *this *= (1 / x);
	}
	double length() const { return sqrt(length_squared()); }
	double length_squared() const { return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; }
	bool near_zero() const {
		const double s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	inline static  vec3 random() {
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max) {
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

public:
	double e[3];
};

using color = vec3;
using point3 = vec3;
// vec3 Utility Functions



inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3& v) {
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3& v, double t) {
	return t * v;
}

inline vec3 operator/(vec3 v, double t) {
	return (1 / t) * v;
}


inline vec3 random_in_unit_disk()
{
	while (true)
	{
		vec3 p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1.0)
			continue;
		return p;
	}
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		auto p = vec3::random(-1, 1);
		if (p.length_squared() >= 1.0) continue;
		return p;
	}
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

inline vec3 random_unit_vecotr() {
	return unit_vector(random_in_unit_sphere());
}



inline double dot(const vec3& u, const vec3& v) {
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}


inline vec3 reflect(const vec3& r, const vec3& n) {
	return r - 2 * dot(r, n) * n;
}

inline vec3 refact(const vec3& uv, const vec3& n, double etai_over_etao) {
	auto cos_theta = fmin(dot(n, -uv), 1.0);
	auto r_out_paralell = etai_over_etao * (uv + cos_theta * n);
	auto r_out_perp = -sqrt(1.0 - r_out_paralell.length_squared()) * n;

	return r_out_perp + r_out_paralell;
}

#endif
