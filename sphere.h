#ifndef RAYTRACING_SPHERE_H
#define RAYTRACING_SPHERE_H

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "hit_record.h"
#include "material.h"

typedef struct sphere {
    point3 center;
    double radius;
    material * mat;
} sphere;

bool hit(sphere * s, ray * r, double t_min, double t_max, hit_record * rec);

#endif //RAYTRACING_SPHERE_H
