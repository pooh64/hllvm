#pragma once

#include <math.h>
#include <stdint.h>

static inline float rsqrtf(float x)
{
	return 1.0f / sqrtf(x);
}

typedef struct float3 {
	float x;
	float y;
	float z;
} float3;

static inline float3 float3_frompixel(uint32_t p)
{
	union {
		uint8_t c[4];
		uint32_t p;
	} u;
	u.p = p;
	return (float3){u.c[0] / 255.0, u.c[1] / 255.0, u.c[2] / 255.0};
}

static inline uint32_t float3_topixel(float3 v)
{
	union {
		uint8_t c[4];
		uint32_t p;
	} u;
	u.c[0] = v.x * 255.0;
	u.c[1] = v.y * 255.0;
	u.c[2] = v.z * 255.0;
	u.c[3] = 255;
	return u.p;
}

static inline float3 float3_add(float3 a, float3 b)
{
	return (float3){a.x + b.x, a.y + b.y, a.z + b.z};
}

static inline float3 float3_sub(float3 a, float3 b)
{
	return (float3){a.x - b.x, a.y - b.y, a.z - b.z};
}

static inline float3 float3_mul(float3 a, float3 b)
{
	return (float3){a.x * b.x, a.y * b.y, a.z * b.z};
}

static inline float3 float3_scale(float3 v, float val)
{
	return (float3){val * v.x, val * v.y, val * v.z};
}

static inline float float3_dot(float3 a, float3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

static inline float3 float3_cross(float3 a, float3 b)
{
	return (float3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

static inline float3 float3_norm(float3 v)
{
	return float3_scale(v, rsqrtf(float3_dot(v, v)));
}

static inline float3 float3_clamp(float3 v)
{
	v.x = (v.x > 1.0f) ? 1.0f : v.x;
	v.y = (v.y > 1.0f) ? 1.0f : v.y;
	v.z = (v.z > 1.0f) ? 1.0f : v.z;
	return v;
}

static inline float3 float3_refl(float3 v, float3 n)
{
	return float3_sub(v, float3_scale(n, 2.0f * float3_dot(n, v)));
}