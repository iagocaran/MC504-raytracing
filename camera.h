#ifndef RAYTRACING_CAMERA_H
#define RAYTRACING_CAMERA_H

#include "vec3.h"
#include "ray.h"


typedef struct camera {
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
} camera;

camera create_camera(point3 lookfrom,
                     point3 lookat,
                     vec3 vup,
                     double vfov,
                     double aspect_ratio,
                     double aperture,
                     double focus_dist);

ray get_ray(camera * cam, double s, double t);

#endif //RAYTRACING_CAMERA_H
