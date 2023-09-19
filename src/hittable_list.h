#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
	hittable_list() {}
	hittable_list(shared_ptr<hittable> object) { add(object); }
	void add(const shared_ptr<hittable>& object) { 
		objects.push_back(object);
		bbox = aabb(bbox, object->bounding_box());
	}
	void clear() { objects.clear(); }
	virtual bool hit(const ray& r, interval ray_t, hit_record& record)const;

	aabb bounding_box() const { return bbox; }

public:
	std::vector<shared_ptr<hittable>> objects;

private:
	aabb bbox;
};

bool hittable_list::hit(const ray& r, interval ray_t, hit_record& record)const {
	hit_record record_tmp;
	auto t_max = ray_t.max;
	bool hit_anything = false;
	
	for (auto& object : objects) {
		if (object->hit(r, interval(ray_t.min, t_max), record_tmp)) {
			hit_anything = true;
			record = record_tmp;
			t_max = record_tmp.t;
		}
	}

	return hit_anything;
}

//bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
//	hit_record temp_rec;
//	bool hit_anything = false;
//	auto closest_so_far = t_max;
//
//	for (const auto& object : objects) {
//		if (object->hit(r, t_min, closest_so_far, temp_rec)) {
//			hit_anything = true;
//			closest_so_far = temp_rec.t;
//			rec = temp_rec;
//		}
//	}
//
//	return hit_anything;
//}

#endif
