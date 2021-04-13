#include "material.h"

bool scatter_lambertian(material * m, ray * r_in, hit_record * rec, color * attenuation, ray * scattered) {
    vec3 scatter_direction = add_vec3(rec->normal, random_unit_vector());

    if (is_near_zero_vec3(scatter_direction)) {
        scatter_direction = rec->normal;
    }

    *scattered = create_ray(rec->p, scatter_direction);
    *attenuation = m->albedo;

    return true;
}

bool scatter_metal(material * m, ray * r_in, hit_record * rec, color * attenuation, ray * scattered) {
    vec3 reflected = reflect(unit_vector(r_in->direction), rec->normal);
    *scattered = create_ray(rec->p, add_vec3(reflected, multiply_vec3_d(random_in_unit_sphere(), m->fuzz_ir)));
    *attenuation = m->albedo;
    return dot(scattered->direction, rec->normal) > 0;
}

static double reflectance(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool scatter_dielectric(material * m, ray * r_in, hit_record * rec, color * attenuation, ray * scattered) {
    *attenuation = create_vec3(1, 1, 1);
    double refraction_ratio = rec->front_face ? (1 / m->fuzz_ir) : m->fuzz_ir;

    vec3 unit_direction = unit_vector(r_in->direction);
    double cos_theta = fmin(dot(invert_vec3(unit_direction), rec->normal), 1.0);
    double sin_theta = sqrt(1 - cos_theta * cos_theta);

    bool cannot_reftact = refraction_ratio * sin_theta > 1;
    vec3 direction;

    if (cannot_reftact || reflectance(cos_theta, refraction_ratio) > random_double())
        direction = reflect(unit_direction, rec->normal);
    else
        direction = refract(unit_direction, rec->normal, refraction_ratio);

    *scattered = create_ray(rec->p, direction);
    return true;
}

material create_lambertian(color c) {
    material m;
    m.albedo = c;
    m.scatter = scatter_lambertian;
    return m;
}

material create_metal(color c, double f) {
    material m;
    m.albedo = c;
    m.fuzz_ir = f;
    m.scatter = scatter_metal;
    return m;
}

material create_dielectric(double i) {
    material m;
    m.fuzz_ir = i;
    m.scatter = scatter_dielectric;
    return m;
}