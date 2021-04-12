#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Vec3 {
  double x;
  double y;
  double z;
};
typedef struct Vec3 *p_vec3;

typedef struct Vec3 Color;
typedef struct Vec3 *p_color;
typedef struct Vec3 Point3;
typedef struct Vec3 *p_point3;

void write_vec3(FILE *out, p_vec3 vec);

p_vec3 create_vec3(double x, double y, double z);

p_vec3 clone_vec3(p_vec3 vec);

p_vec3 create_random_vec3();

p_vec3 create_random_interval_vec3(double low, double high);

void invert_vec3(p_vec3 vec);

void add_vec3(p_vec3 left, p_vec3 right);

void add_scalar_vec3(p_vec3 vec, double scalar);

void subtract_vec3(p_vec3 left, p_vec3 right);

void subtract_scalar_vec3(p_vec3 vec, double scalar);

double dot_product_vec3(p_vec3 vec1, p_vec3 vec2);

void cross_product_vec3(p_vec3 left, p_vec3 right);

void multiply_scalar_vec3(p_vec3 vec, double scalar);

void divide_scalar_vec3(p_vec3 vec, double scalar);

double length_vec3(p_vec3 vec);

int is_near_zero_vec3(p_vec3 vec);

void unit_vector_vec3(p_vec3 vec);

p_vec3 random_unit_vector_vec3();

p_vec3 random_in_hemisphere_vec3(p_vec3 normal);

p_vec3 random_in_unit_disk_vec3();

void reflect_vec3(p_vec3 vec, p_vec3 normal);

p_vec3 refract_vec3(p_vec3 unit_vec, p_vec3 normal, double etai_over_etat);

#endif  // RAYTRACING_VEC3_H
