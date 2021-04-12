#ifndef RAY_H
#define RAY_H

#include "vec3.h"

typedef struct ray {
	point3 orig;
        vec3 dir;

        void (*ray)();
        void (*ray)(ray,point3,vec3);
        point3 (*at_ptr)(ray,double);
};
void ray() {}

void ray(ray &r,const point3& origins, const vec3& directions){
	if (r == NULL) return 0;
	r->orig = origins;
	r->dir = directions;
	r->at_ptr = at;
}

point3 at(ray &r, double t) const {
	return r->orig + t*(r->dir);
}
#endif

