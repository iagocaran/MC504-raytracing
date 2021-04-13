#include "vec3.h"

inline vec3 create_vec3(double x, double y, double z) {
    vec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

inline vec3 clone_vec3(vec3 vec) {
    return create_vec3(vec.x, vec.y, vec.z);
}

inline vec3 create_random_interval_vec3(double low, double high) {
    return create_vec3(random_double(low, high), random_double(low, high),
                                         random_double(low, high));
}

inline vec3 create_random_vec3() {
    return create_random_interval_vec3(-100, 100);
}

inline vec3 invert_vec3(vec3 vec) {
    vec3 out;
    out.x = -vec.x;
    out.y = -vec.y;
    out.z = -vec.z;
    return out;
}

inline vec3 add_vec3(vec3 left, vec3 right) {
    vec3 out;
    out.x = left.x + right.x;
    out.y = left.y + right.y;
    out.z = left.z + right.z;
    return out;
}

inline vec3 add_scalar_vec3(vec3 vec, double scalar) {
    vec3 out;
    out.x = vec.x + scalar;
    out.y = vec.y + scalar;
    out.z = vec.z + scalar;
    return out;
}

inline vec3 subtract_vec3(vec3 left, vec3 right) {
    vec3 out;
    out.x = left.x - right.x;
    out.y = left.y - right.y;
    out.z = left.z - right.z;
    return out;
}

inline vec3 subtract_vec3_d(vec3 vec, double scalar) {
    return add_scalar_vec3(vec, -scalar);
}

inline double dot(vec3 vec1, vec3 vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

inline vec3 cross(vec3 left, vec3 right) {
    vec3 out;

    out.x = left.y * right.z - left.z * right.y;
    out.y = left.z * right.x - left.x * right.z;
    out.z = left.x * right.y - left.y * right.x;

    return out;
}

inline vec3 multiply_vec3_d(vec3 vec, double scalar) {
    vec3 out;
    out.x = vec.x * scalar;
    out.y = vec.y * scalar;
    out.z = vec.z * scalar;
    return out;
}

inline vec3 divide_vec3_d(vec3 vec, double scalar) {
    return multiply_vec3_d(vec, 1 / scalar);
}

inline double length_squared_vec3(vec3 vec) { return dot(vec, vec); }

inline double length_vec3(vec3 vec) { return sqrt(length_squared_vec3(vec)); }

int is_near_zero_vec3(vec3 vec) {
    const double s = 1e-8;
    return fabs(vec.x) < s && fabs(vec.y) < s && (vec.z) < s;
}

inline vec3 unit_vector(vec3 vec) {
    return divide_vec3_d(vec, length_vec3(vec));
}

vec3 random_in_unit_sphere() {
    vec3 vec = create_random_interval_vec3(-1, 1);
    while (length_squared_vec3(vec) >= 1) {
        vec = create_random_interval_vec3(-1, 1);
    }
    return vec;
}

vec3 random_unit_vector() {
    vec3 vec = random_in_unit_sphere();
    unit_vector(vec);
    return vec;
}

vec3 random_in_hemisphere_vec3(vec3 normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    double prod = dot(in_unit_sphere, normal);
    if (prod <= 0.0) {
        invert_vec3(in_unit_sphere);
    }
    return in_unit_sphere;
}

vec3 random_in_unit_disk_vec3() {
    vec3 vec = create_random_interval_vec3(-1, 1);
    vec.z = 0;
    while (length_squared_vec3(vec) >= 1) {
        vec = create_random_interval_vec3(-1, 1);
        vec.z = 0;
    }
    return vec;
}

vec3 reflect_vec3(vec3 vec, vec3 normal) {
    return subtract_vec3(vec, multiply_vec3_d(normal, 2 * dot(vec, normal)));
}

vec3 refract_vec3(vec3 unit_vec, vec3 normal, double etai_over_etat) {
    double cos_theta = fmin(dot(invert_vec3(unit_vec), normal), 1);
    vec3 r_out_perp = multiply_vec3_d(add_vec3(unit_vec, multiply_vec3_d(normal, cos_theta)), etai_over_etat);
    vec3 r_out_parallel = multiply_vec3_d(normal, - sqrt(fabs(1.0 - length_squared_vec3(r_out_perp))));
    return add_vec3(r_out_perp, r_out_parallel);
}
