#ifndef RAYTRACING_RTWEEKEND_H
#define RAYTRACING_RTWEEKEND_H

#include <stdlib.h>
#include <math.h>
#include <limits.h>

double inline degrees_to_radians(double degrees) {
    return degrees * 3.1415926535897932385 / 180;
}

double inline random_double() {
    return rand() / (RAND_MAX + 1.0);
}

double inline random_double_within_limits(double min, double max) {
    return min + (max - min) * random_double();
}

double inline clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif //RAYTRACING_RTWEEKEND_H
