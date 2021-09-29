#pragma once

#include "upt/ray_core.h"

#define ALLOC_SHAPE(name)                                                                          \
	({                                                                                         \
		name *_ptr = xmalloc(sizeof(*_ptr));                                               \
		_ptr->base.Hit = (void *)name##Hit;                                                \
		_ptr;                                                                              \
	})

typedef struct Sphere {
	Shape base;
	Material *material;
	float r;
	float3 o;
} Sphere;

bool SphereHit(Sphere *this, HitRecord *hit, float tmin, float tmax);