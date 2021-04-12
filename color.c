#include "color.h"

double clamp(double value, double low, double high) {
  return fmin(fmax(value, low), high);
}

int get_color(double value) { return (int)(256 * clamp(value, 0.0, 0.999)); }

void write_color(FILE *out, p_color pixel_color, int samples_per_pixel) {
  double r = pixel_color->x;
  double g = pixel_color->y;
  double b = pixel_color->z;

  double scale = 1.0 / samples_per_pixel;
  r = sqrt(scale * r);
  g = sqrt(scale * g);
  b = sqrt(scale * b);

  fprintf(out, "%d %d %d\n", get_color(r), get_color(g), get_color(b));
}