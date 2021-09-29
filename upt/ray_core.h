#pragma once

#include "upt/float3.h"
#include "upt/util.h"
#include <stdbool.h>

typedef float3 Color;
typedef struct Ray Ray;
typedef struct HitRecord HitRecord;
typedef struct Shape Shape;
typedef struct Material Material;
typedef struct Camera Camera;
typedef struct Scene Scene;

struct Ray {
	float3 o, d;
};

static inline float3 RayAt(Ray const r, float t)
{
	return float3_add(r.o, float3_scale(r.d, t));
}

struct HitRecord {
	Ray ray;
	float3 sn;
	float t;
	Material *material;
};

struct Material {
	bool (*Apply)(Material const *mat, HitRecord *hit, Color *color);
};

struct Shape {
	bool (*Hit)(Shape *shape, HitRecord *hit, float tmin, float tmax);
};

struct Camera {
	float3 pos, dir, axis_x, axis_y;
	float ratio; // res_x / res_y
	float fov;   // axis_y in rad
};

static inline void CameraSetScreen(Camera *cam, float fov, float ratio)
{
	cam->fov = fov;
	cam->ratio = ratio;
}

static inline void CameraLookAt(Camera *cam, float3 const eye, float3 const at, float3 const up)
{
	cam->pos = eye;
	cam->dir = float3_norm(float3_sub(at, eye));
	cam->axis_x = float3_norm(float3_cross(cam->dir, up));
	cam->axis_y = float3_cross(cam->axis_x, cam->dir);

	cam->axis_x = float3_scale(cam->axis_x, cam->ratio * cam->fov);
	cam->axis_y = float3_scale(cam->axis_y, cam->fov);
}

static inline Ray CameraCast(Camera const *cam, float x, float y)
{
	Ray r = {.o = cam->pos,
		 .d = float3_add(cam->dir, float3_add(float3_scale(cam->axis_x, x),
						      float3_scale(cam->axis_y, y)))};
	r.d = float3_norm(r.d);
	return r;
}

struct Scene {
	Shape **shapes;
	size_t nshapes;
	Camera camera;
	float3 sky_color;
};