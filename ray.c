#include "ray.h"

ray create_ray(const point3 origins, const vec3 directions){
    ray r;
    r.origin = clone_vec3(origins);
    r.direction = clone_vec3(directions);

    return r;
}

point3 at(ray *r, double t) {
    return add_vec3(r->origin, multiply_vec3_d(r->direction, t));
}
