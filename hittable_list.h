#ifndef RAYTRACING_HITTABLE_LIST_H
#define RAYTRACING_HITTABLE_LIST_H

#include "hittable.h"

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

typedef struct hittable_list {
    struct hittable h;
    Array objects;
    initArray(objects, 10);
} hittable_list;

void hittable_list() {}

void hittable_list(hittable_list hl, hittable* object) {
    insertArray(hl->objects, object);
}

void clear (hittable_list hl) {
    freeArray(hl->objects);
}

void add(hittable_list hl, hittable* object) {
    insertArray(hl->objects, object);
}

virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override; 

bool hittable_list::hit(hittable_list hl, hittable* object, const ray &r, double t_min, double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : hl->objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif //RAYTRACING_HITTABLE_LIST_H