#pragma once

#include "vec3.h"
#include <iostream>
#include "rtweekend.h"

inline void write_color(std::ostream& out, const color& pixel_color, int pixel_sample_num) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();
	double scale = 1.0 / pixel_sample_num;
	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b *scale);
	out << static_cast<int>(256 * clamp(r, 0.0, 0.9999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.9999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.9999)) << '\n';
}
