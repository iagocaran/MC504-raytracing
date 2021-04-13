#ifndef RAYTRACING_HIT_RECORD_H
#define RAYTRACING_HIT_RECORD_H

struct material;

typedef struct hit_record {
    point3 p;
    vec3 normal;
    struct material * mat_ptr;
    double t;
    bool front_face;
} hit_record;

#endif //RAYTRACING_HIT_RECORD_H
