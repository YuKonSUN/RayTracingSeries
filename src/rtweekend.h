#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

//using

using std::shared_ptr;
using std::sqrt;
using std::make_shared;

//Constants

const double pi = 3.1415926535897932385;
const double infinity = std::numeric_limits<double>::infinity();
const int max_recursive_depth = 10;

//Unity functions

inline double degree_to_radians(double degree) {
	return degree * pi / 180.0;
}

inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
	return min + (max - min) * random_double();
}

inline double clamp(double x, double min, double max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline int random_int(int min, int max) {
	return static_cast<int>(random_double(min, max + 1));
}


//Common Headers


#endif
