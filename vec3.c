#include "vec3.h"

#ifndef RAND_MAX
#define RAND_MAX ((int)((unsigned)~0 >> 1))
#endif

double random_double(double low, double high) {
  double d;

  d = (double) rand() / ((double)RAND_MAX + 1);
  return (low + d * (high - low));
}

vec3 * create_vec3(double x, double y, double z) {
  vec3 * vec = malloc(sizeof(struct vec3));
  vec->x = x;
  vec->y = y;
  vec->z = z;
  return vec;
}

vec3 * clone_vec3(vec3 * vec) { return create_vec3(vec->x, vec->y, vec->z); }

vec3 * create_random_interval_vec3(double low, double high) {
  return create_vec3(random_double(low, high), random_double(low, high),
                     random_double(low, high));
}

vec3 * create_random_vec3() { return create_random_interval_vec3(-100, 100); }

void invert_vec3(vec3 * vec) {
  vec->x = -vec->x;
  vec->y = -vec->y;
  vec->z = -vec->z;
}

void add_vec3(vec3 * left, vec3 * right) {
  left->x = left->x + right->x;
  left->y = left->y + right->y;
  left->z = left->z + right->z;
}

void add_scalar_vec3(vec3 * vec, double scalar) {
  vec->x = vec->x + scalar;
  vec->y = vec->y + scalar;
  vec->z = vec->z + scalar;
}

void subtract_vec3(vec3 * left, vec3 * right) {
  left->x = left->x - right->x;
  left->y = left->y - right->y;
  left->z = left->z - right->z;
}

void subtract_scalar_vec3(vec3 * vec, double scalar) {
  add_scalar_vec3(vec, -scalar);
}

double dot_product_vec3(vec3 * vec1, vec3 * vec2) {
  return vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
}

void cross_product_vec3(vec3 * left, vec3 * right) {
  double left_x = left->x;
  double left_y = left->y;
  double left_z = left->z;

  left->x = left_y * right->z - left_z * right->y;
  left->y = left_z * right->x - left_x * right->z;
  left->z = left_x * right->y - left_y * right->x;
}

void multiply_scalar_vec3(vec3 * vec, double scalar) {
  vec->x = vec->x * scalar;
  vec->y = vec->y * scalar;
  vec->z = vec->z * scalar;
}

void divide_scalar_vec3(vec3 * vec, double scalar) {
  return multiply_scalar_vec3(vec, 1 / scalar);
}

double length_squared_vec3(vec3 * vec) { return dot_product_vec3(vec, vec); }

double length_vec3(vec3 * vec) { return sqrt(length_squared_vec3(vec)); }

int is_near_zero_vec3(vec3 * vec) {
  const double s = 1e-8;
  return fabs(vec->x) < s && fabs(vec->y) < s && (vec->z) < s;
}

void unit_vector_vec3(vec3 * vec) { divide_scalar_vec3(vec, length_vec3(vec)); }

vec3 * random_in_unit_sphere() {
  vec3 * vec = create_random_interval_vec3(-1, 1);
  while (length_squared_vec3(vec) >= 1) {
    free(vec);
    vec = create_random_interval_vec3(-1, 1);
  }
  return vec;
}

vec3 * random_unit_vector_vec3() {
  vec3 * vec = random_in_unit_sphere();
  unit_vector_vec3(vec);
  return vec;
}

vec3 * random_in_hemisphere_vec3(vec3 * normal) {
  vec3 * in_unit_sphere = random_in_unit_sphere();
  double prod = dot_product_vec3(in_unit_sphere, normal);
  if (prod <= 0.0) {
    invert_vec3(in_unit_sphere);
  }
  return in_unit_sphere;
}

vec3 * random_in_unit_disk_vec3() {
  vec3 * vec = create_random_interval_vec3(-1, 1);
  vec->z = 0;
  while (length_squared_vec3(vec) >= 1) {
    free(vec);
    vec = create_random_interval_vec3(-1, 1);
    vec->z = 0;
  }
  return vec;
}

void reflect_vec3(vec3 * vec, vec3 * normal) {
  vec3 * aux_normal = clone_vec3(normal);

  double dp = 2 * dot_product_vec3(vec, normal);
  multiply_scalar_vec3(aux_normal, dp);
  subtract_vec3(vec, aux_normal);

  free(aux_normal);
}

vec3 * refract_vec3(vec3 * unit_vec, vec3 * normal, double etai_over_etat) {
  vec3 * inverse_unit_vec = clone_vec3(unit_vec);
  vec3 * perpendicular_vec = clone_vec3(normal);
  vec3 * parallel_vec = clone_vec3(normal);
  invert_vec3(inverse_unit_vec);

  double cos_theta = fmin(dot_product_vec3(inverse_unit_vec, normal), 1.0);
  multiply_scalar_vec3(perpendicular_vec, cos_theta);
  add_vec3(perpendicular_vec, unit_vec);
  multiply_scalar_vec3(perpendicular_vec, etai_over_etat);

  multiply_scalar_vec3(
      parallel_vec, -sqrt(fabs(1.0 - length_squared_vec3(perpendicular_vec))));
  add_vec3(parallel_vec, perpendicular_vec);

  free(inverse_unit_vec);
  free(perpendicular_vec);
  return parallel_vec;
}
