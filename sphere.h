#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "material.h"

typedef struct hit_record {
    point3 p;
    vec3 normal;
    material * mat_ptr;
    double t;
    bool front_face;
} hit_record;

typedef struct sphere {
    point3 center;
    double radius;
    material * mat;
} sphere;

bool hit(sphere * s, ray * r, double t_min, double t_max, hit_record * rec);

#endif //RAYTRACING_SPHERE_H
