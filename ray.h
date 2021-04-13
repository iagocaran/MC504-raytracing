#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "vec3.h"

typedef struct ray {
    point3 origin;
    vec3 direction;
} ray;

ray create_ray(point3 origins, vec3 directions);

point3 at(ray *r, double t);

#endif //RAYTRACING_RAY_H
