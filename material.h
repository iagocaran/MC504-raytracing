#ifndef RAYTRACING_MATERIAL_H
#define RAYTRACING_MATERIAL_H

#include "stdbool.h"
#include "color.h"
#include "ray.h"
#include "hit_record.h"

typedef struct material {
    color albedo;
    double fuzz_ir;
    bool (*scatter)(struct material* m, ray* r_in, hit_record* rec, color* attenuation, ray* scattered);
} material;

bool scatter_lambertian(material * m, ray * r_in, hit_record * rec, color * attenuation, ray * scattered);
bool scatter_metal(material * m, ray * r_in, hit_record * rec, color * attenuation, ray * scattered);
bool scatter_dielectric(material * m, ray * r_in, hit_record * rec, color * attenuation, ray * scattered);

material create_lambertian(color c);
material create_metal(color c, double f);
material create_dielectric(double i);

#endif //RAYTRACING_MATERIAL_H
