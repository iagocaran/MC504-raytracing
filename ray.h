//
// Created by iagoc on 01/03/2021.
//

#ifndef RAYTRACING_RAY_H
#define RAYTRACING_RAY_H

#include "vec3.h"

class ray {
    public:
        ray() = default;
        ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {};

        point3 origin() const { return orig; }
        vec3 direction() const { return dir; }

        point3 at(double t) const {
            return orig + t * dir;
        }

        point3 orig;
        vec3 dir;
};

#endif //RAYTRACING_RAY_H
