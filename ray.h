#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "vec3.h"

typedef struct ray {
    point3 origin;
    vec3 direction;
} ray;

ray create_ray(const point3 * origins, const vec3 * directions){
    ray r;
    r.origin = clone_vec3(*origins);
    r.direction = clone_vec3(*directions);
}

point3 at(ray *r, double t) {
    return add_vec3(r->origin, multiply_vec3_d(r->direction, t));
}

#endif //RAYTRACING_RAY_H
