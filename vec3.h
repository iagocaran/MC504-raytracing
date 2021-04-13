#ifndef RAYTRACING_VEC3_H
#define RAYTRACING_VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "rtweekend.h"

typedef struct vec3 {
  double x;
  double y;
  double z;
} vec3;

typedef struct vec3 point3;
typedef struct vec3 color;

vec3 create_vec3(double x, double y, double z);

vec3 clone_vec3(vec3 vec);

vec3 create_random_vec3();

vec3 create_random_interval_vec3(double low, double high);

inline vec3 invert_vec3(vec3 vec);

inline vec3 add_vec3(vec3 left, vec3 right);

inline vec3 add_vec3_d(vec3 vec, double scalar);

vec3 subtract_vec3(vec3 left, vec3 right);

vec3 subtract_vec3_d(vec3 vec, double scalar);

double dot_product_vec3(vec3 vec1, vec3 vec2);

vec3 cross_product_vec3(vec3 left, vec3 right);

inline vec3 multiply_vec3_d(vec3 vec, double scalar);

inline vec3 divide_vec3_d(vec3 vec, double scalar);

double length_vec3(vec3 vec);

int is_near_zero_vec3(vec3 vec);

inline vec3 unit_vector_vec3(vec3 vec);

vec3 random_unit_vector_vec3();

vec3 random_in_hemisphere_vec3(vec3 normal);

vec3 random_in_unit_disk_vec3();

vec3 reflect_vec3(vec3 vec, vec3 normal);

vec3 refract_vec3(vec3 unit_vec, vec3 normal, double etai_over_etat);

#endif  // RAYTRACING_VEC3_H
