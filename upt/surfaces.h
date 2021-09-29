#pragma once

#include "upt/ray_core.h"

#define DEF_MATERIAL_APPLY(name) bool name##Apply(name const *this, HitRecord *hit, float3 *color)

#define ALLOC_MATERIAL(name)                                                                       \
	({                                                                                         \
		name *_ptr = xmalloc(sizeof(*_ptr));                                               \
		_ptr->base.Apply = (void *)name##Apply;                                            \
		_ptr;                                                                              \
	})

typedef struct Mirror {
	Material base;
	float3 color;
} Mirror;
DEF_MATERIAL_APPLY(Mirror);

typedef struct Lamp {
	Material base;
	float3 color;
} Lamp;
DEF_MATERIAL_APPLY(Lamp);

typedef struct Lambert {
	Material base;
	float3 color;
} Lambert;
DEF_MATERIAL_APPLY(Lambert);

typedef struct Glass {
	Material base;
	float3 color;
} Glass;
DEF_MATERIAL_APPLY(Glass);

typedef struct Phong {
	Material base;
	float3 color;
	float pexp;
} Phong;
DEF_MATERIAL_APPLY(Phong);