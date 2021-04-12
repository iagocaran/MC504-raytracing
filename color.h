#ifndef RAYTRACING_COLOR_H
#define RAYTRACING_COLOR_H

#include <math.h>
#include <stdio.h>

#include "vec3.h"

void write_color(FILE *out, p_color pixel_color, int samples_per_pixel);

#endif  // RAYTRACING_COLOR_H
