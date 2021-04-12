#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

typedef struct hit_record {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
};

typedef struct hittable {
        virtual bool (*hit_ptr)(const ray,double,double,hit_record);
};
void hittable(){
	hittable->hit_ptr = hit;
}
virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

inline void set_face_normal(const ray& r, const vec3& outward_normal) {
	front_face = dot(r.direction(r), outward_normal) < 0;
	normal = front_face ? outward_normal :-outward_normal;
}

#endif
