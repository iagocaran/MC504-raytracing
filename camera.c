#include "camera.h"
#include "math.h"
#include "ray.h"

camera create_camera(point3 lookfrom,
                     point3 lookat,
                     vec3 vup,
                     double vfov,
                     double aspect_ratio,
                     double aperture,
                     double focus_dist) {
    camera cam;

    double theta = degrees_to_radians(vfov);
    double h = tan(theta / 2);

    double viewport_height  = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    cam.w = unit_vector(subtract_vec3(lookfrom, lookat));
    cam.u = unit_vector(cross(vup, cam.w));
    cam.v = cross(cam.w, cam.u);

    cam.origin = lookat;
    cam.horizontal = multiply_vec3_d(cam.u, focus_dist * viewport_width);
    cam.vertical = multiply_vec3_d(cam.v, focus_dist * viewport_height);
    cam.lower_left_corner = subtract_vec3(
            subtract_vec3(cam.origin, divide_vec3_d(cam.horizontal, 2)),
            add_vec3(divide_vec3_d(cam.vertical, 2), multiply_vec3_d(cam.w, focus_dist)));

    cam.lens_radius = aperture / 2;

    return cam;
}

ray get_ray(camera * cam, double s, double t) {
    vec3 rd = multiply_vec3_d(random_in_unit_disk_vec3(), cam->lens_radius);
    vec3 offset = add_vec3(multiply_vec3_d(cam->u, rd.x), multiply_vec3_d(cam->v, rd.y));

    return create_ray(
            add_vec3(cam->origin, offset),
            add_vec3(cam->lower_left_corner,
                     subtract_vec3(add_vec3(multiply_vec3_d(cam->horizontal, s),
                                            multiply_vec3_d(cam->vertical, t)),
                                   add_vec3(cam->origin, offset)))
            );
}
