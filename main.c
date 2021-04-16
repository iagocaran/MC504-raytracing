#include <stdio.h>
#include <stdlib.h>

#include "rtweekend.h"
#include "color.h"
#include "sphere.h"
#include "camera.h"

bool world_hit(sphere * world, int n, ray * r, double t_min, double t_max, struct hit_record * rec) {
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_max;

    for (int i = 0; i < n; i++) {
        if (hit(&world[i], r, t_min, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *rec = temp_rec;
        }
    }

    return hit_anything;
}

color ray_color(ray * r, sphere * world, int n, int depth) {
    hit_record rec;

    if (depth <= 0)
        return create_vec3(0, 0, 0);

    if (world_hit(world, n, r, 0.001, INFINITY, &rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(rec.mat_ptr, r, &rec, &attenuation, &scattered))
            return multiply_vec3_vec3(attenuation, ray_color(&scattered, world, n, depth - 1));
        return create_vec3(0, 0, 0);
    }

    vec3 unit_direction = unit_vector(r->direction);
    double t = 0.5 * (unit_direction.y + 1.0);
    color pixel_color = add_vec3(multiply_vec3_d(create_vec3(1.0, 1.0, 1.0), 1.0 - t),
                               multiply_vec3_d(create_vec3(0.5, 0.7, 1.0), t));
    return pixel_color;
}

int random_scene(sphere* world) {
    int i = 0;

    material* t = malloc(sizeof(material));
    *t = create_lambertian(create_vec3(0.5, 0.5, 0.5));
    world[i++] = create_sphere(create_vec3(0, -1000, 0), 1000, t);

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_mat = random_double();
            point3 center = create_vec3(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if (length_vec3(subtract_vec3(center, create_vec3(4, 0.2, 0))) > 0.9) {
                material * sphere_material = malloc(sizeof(material));

                if (choose_mat < 0.8) {
                    color albedo = multiply_vec3_vec3(create_random_vec3(), create_random_vec3());
                    *sphere_material = create_lambertian(albedo);
                    world[i++] = create_sphere(center, 0.2, sphere_material);
                } else if (choose_mat < 0.95) {
                    color albedo = create_random_interval_vec3(0.5, 1);
                    double fuzz = random_double(0, 0.5);
                    *sphere_material = create_metal(albedo, fuzz);
                    world[i++] = create_sphere(center, 0.2, sphere_material);
                } else if (sphere_material) {
                    *sphere_material = create_dielectric(1.5);
                    world[i++] = create_sphere(center, 0.2, sphere_material);
                }
            }
        }
    }

    t = malloc(sizeof(material));
    *t = create_dielectric(1.5);
    world[i++] = create_sphere(create_vec3(0, 1, 0), 1.0, t);

    t = malloc(sizeof(material));
    *t = create_lambertian(create_vec3(0.4, 0.2, 0.1));
    world[i++] = create_sphere(create_vec3(-4, 1, 0), 1.0, t);

    t = malloc(sizeof(material));
    *t = create_metal(create_vec3(0.7, 0.6, 0.5), 0);
    world[i++] = create_sphere(create_vec3(4, 1, 0), 1.0, t);

    return i;
}

int main() {
    // Image

    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 600;
    const int image_height = (int) (image_width / aspect_ratio);
    const int samples_per_pixel = 50;
    const int max_depth = 10;

    //World

    sphere* world = malloc(500 * sizeof(sphere));
    int size = random_scene(world);

    // Camera

    point3 lookfrom = create_vec3(13,2,3);
    point3 lookat = create_vec3(0,0,0);
    vec3 vup = create_vec3(0,1,0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;

    camera cam = create_camera(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    fprintf(stdout, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = image_height - 1; j >= 0; --j) {
        fprintf(stderr, "P3\n%d %d\n255\n", image_width, image_height);
        fprintf(stderr, "\rScanlines remaining: %d", j);
        fflush(stderr);
        for (int i = 0; i < image_width; ++i) {
            color pixel_color = create_vec3(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                double u = (i + random_double()) / (image_width - 1);
                double v = (j + random_double()) / (image_height - 1);
                ray r = get_ray(&cam, u, v);
                pixel_color = add_vec3(pixel_color, ray_color(&r, world, size, max_depth));
            }
            write_color(stdout, &pixel_color, samples_per_pixel);
        }
    }

    fprintf(stderr, "\nDone.\n");

    return EXIT_SUCCESS;
}