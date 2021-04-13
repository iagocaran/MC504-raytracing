#include "sphere.h"

inline void set_face_normal(hit_record * rec, ray * r, const vec3 outward_normal) {
    rec->front_face = dot(r->direction, outward_normal) < 0;
    rec->normal = rec->front_face ? outward_normal : invert_vec3(outward_normal);
}

bool hit(sphere * s, ray * r, double t_min, double t_max, hit_record * rec) {
    vec3 oc = subtract_vec3(r->origin, s->center);
    double a = length_squared(r->direction);
    double half_b = dot(oc, r->direction);
    double c = length_squared(oc) - s->radius * s->radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    double sqrtd = sqrt(discriminant);

    double root = (- half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec->t = root;
    rec->p = at(r, rec->t);
    vec3 outward_normal = divide_vec3_d(subtract_vec3(rec->p, s->center), s->radius);
    set_face_normal(rec, r, outward_normal);
    rec->mat_ptr = s->mat;

    return true;
}
