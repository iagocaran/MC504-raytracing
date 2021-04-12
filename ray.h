#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
	point3 orig;
        vec3 dir;

        void ray();
        void ray(ray &r,const point3& origin, const vec3& direction);
        point3 origin(ray &r);
        vec3 direction(ray &r);
        point3 at(ray &r, double t);
};
ray() {}

void ray(ray &r,const point3& origins, const vec3& directions){
	if (r == NULL) return 0;
	r->origin(origins);
	r->direction(directions);

}

point3 origin(ray &r) const  { return r->orig; }
vec3 direction(ray &r) const { return r->dir; }
point3 at(ray &r, double t) const {
	return r->orig + t*(r->dir);
}
#endif
