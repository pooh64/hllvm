#include "upt/float3.h"
#include "uvideomem/uvideomem.h"
#include <float.h>
#include <stdlib.h>

#include "upt/ray_core.h"
#include "upt/shapes.h"
#include "upt/surfaces.h"

static void place_on_surf(Sphere *a, Sphere *b)
{
	float rs = a->r + b->r;
	float dx = a->o.x - b->o.x;
	float dz = a->o.z - b->o.z;
	a->o.y = b->o.y + sqrtf(rs * rs - dx * dx - dz * dz) + 0.0002;
}

struct Scene Scene1_init()
{
	float3 const sky_color = {0.34f, 0.3f, 0.4f};

	Camera cam;
	CameraSetScreen(&cam, 3.14f / 3.0, (float)UVIDEOMEM_W / (float)UVIDEOMEM_H);
	CameraLookAt(&cam, (float3){0.0f, 0.0f, -0.4f}, (float3){0.0f, 0.0f, 0.0f},
		     (float3){0.0f, -1.0f, 0.0f});

	Lambert *lambert1 = ALLOC_MATERIAL(Lambert);
	lambert1->color = (float3){0.8f, 0.8f, 0.8f};
	Lambert *lambert2 = ALLOC_MATERIAL(Lambert);
	lambert2->color = (float3){0.9f, 0.7f, 0.7f};
	Lambert *lambert3 = ALLOC_MATERIAL(Lambert);
	lambert3->color = (float3){0.7f, 0.4f, 1.0f};
	Lamp *lamp1 = ALLOC_MATERIAL(Lamp);
	lamp1->color = (float3){1.0f, 0.8f, 0.25f};
	Lamp *lamp2 = ALLOC_MATERIAL(Lamp);
	lamp2->color = (float3){0.9f, 0.7f, 0.8f};
	Lamp *lamp3 = ALLOC_MATERIAL(Lamp);
	lamp3->color = (float3){1.0f, 1.0f, 1.0f};
	Mirror *mirror1 = ALLOC_MATERIAL(Mirror);
	mirror1->color = (float3){0.95f, 0.95f, 0.95f};
	Glass *glass1 = ALLOC_MATERIAL(Glass);
	glass1->color = (float3){0.95f, 0.95f, 0.95f};
	Phong *phong1 = ALLOC_MATERIAL(Phong);
	phong1->color = (float3){0.95f, 0.95f, 0.95f};
	phong1->pexp = 3.0f;
	Phong *phong2 = ALLOC_MATERIAL(Phong);
	phong2->color = (float3){0.95f, 0.65f, 0.85f};
	phong2->pexp = 16.0f;
	Phong *phong3 = ALLOC_MATERIAL(Phong);
	phong3->color = (float3){0.70f, 1.0f, 0.95f};
	phong3->pexp = 80.0f;

	size_t nsph = 18;
	Sphere **sph = xmalloc(sizeof(Sphere *) * nsph);
	for (size_t i = 0; i < nsph; ++i)
		sph[i] = ALLOC_SHAPE(Sphere);

	size_t sp = 0;
	sph[sp]->r = M_SQRT2 * 100.0f;
	sph[sp]->o = (float3){1.0f, -106.0f, 100.0f};
	sph[sp]->material = (Material *)lambert1;
	sp++;

	sph[sp]->r = 0.5f;
	sph[sp]->o = (float3){1.5f, 0.0f, 5.0f};
	sph[sp]->material = (Material *)lamp1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.6f;
	sph[sp]->o = (float3){3.0f, 0.0f, 7.0f};
	sph[sp]->material = (Material *)lamp2;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.8f;
	sph[sp]->o = (float3){-1.0f, 0.0f, 4.0f};
	sph[sp]->material = (Material *)lambert2;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 2.2f;
	sph[sp]->o = (float3){-2.5f, 0.0f, 7.5f};
	sph[sp]->material = (Material *)mirror1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.8f;
	sph[sp]->o = (float3){-3.0f, 1.5f, 5.0f};
	sph[sp]->material = (Material *)lamp3;
	sp++;

	sph[sp]->r = 1.5f;
	sph[sp]->o = (float3){3.0f, 0.0f, 9.0f};
	sph[sp]->material = (Material *)mirror1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.4f;
	sph[sp]->o = (float3){1.5f, 0.35f, 2.2f};
	sph[sp]->material = (Material *)glass1;
	sp++;

	sph[sp]->r = 0.6f;
	sph[sp]->o = (float3){-3.2f, 1.5f, 5.2f};
	sph[sp]->material = (Material *)phong1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.6f;
	sph[sp]->o = (float3){-2.0f, 1.5f, 6.0f};
	sph[sp]->material = (Material *)phong2;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.6f;
	sph[sp]->o = (float3){-1.0f, 1.5f, 7.0f};
	sph[sp]->material = (Material *)phong3;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.5f;
	sph[sp]->o = (float3){0.3f, 1.5f, 6.5f};
	sph[sp]->material = (Material *)lambert3;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.4f;
	sph[sp]->o = (float3){-1.0f, 1.5f, 5.8f};
	sph[sp]->material = (Material *)lamp1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.35f;
	sph[sp]->o = (float3){1.5f, 1.5f, 4.5f};
	sph[sp]->material = (Material *)glass1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.4f;
	sph[sp]->o = (float3){2.7f, 1.5f, 5.0f};
	sph[sp]->material = (Material *)glass1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.5f;
	sph[sp]->o = (float3){0.4f, 1.5f, 5.2f};
	sph[sp]->material = (Material *)mirror1;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.8f;
	sph[sp]->o = (float3){1.5f, 0.0f, 7.0f};
	sph[sp]->material = (Material *)lambert2;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	sph[sp]->r = 0.4f;
	sph[sp]->o = (float3){0.3f, 1.5f, 4.0f};
	sph[sp]->material = (Material *)phong2;
	place_on_surf(sph[sp], sph[0]);
	sp++;

	assert(sp == nsph);

	return (Scene){
	    .shapes = (Shape **)sph, .nshapes = nsph, .camera = cam, .sky_color = sky_color};
}

static inline bool PTSceneHit(Shape **shapes, size_t nshapes, HitRecord *hit)
{
	float tmax = FLT_MAX;
	HitRecord cur_hit = *hit;
	bool was_hit = false;
	for (size_t i = 0; i < nshapes; ++i) {
		if (!shapes[i]->Hit(shapes[i], &cur_hit, 0.0001f, tmax))
			continue;
		if (cur_hit.t < tmax) {
			*hit = cur_hit;
			tmax = cur_hit.t;
			was_hit = true;
		}
	}
	return was_hit;
}

static void PTSceneTrace(Scene *scene, Ray const *ray, float3 *color)
{
	float3 rayclr = {1.0f, 1.0f, 1.0f};
	HitRecord hit;
	hit.ray = *ray;
	bool cast = true;

	for (int i = 0; cast; ++i) {
		if (!PTSceneHit(scene->shapes, scene->nshapes, &hit) || i == 64) {
			rayclr = float3_mul(rayclr, scene->sky_color);
			break;
		}
		cast = hit.material->Apply(hit.material, &hit, &rayclr);
	}
	*color = rayclr;
}

void upt_main()
{
	Scene scene = Scene1_init();
	int const nsamples = 8;
	float npass = 1.0;
	uint32_t *vmem = (uint32_t *)uvideomem;
again:
	for (int32_t y = 0; y < UVIDEOMEM_H; ++y) {
		for (int32_t x = 0; x < UVIDEOMEM_W; ++x) {
			float3 rayclr = {0};
			for (int i = 0; i < nsamples; ++i) {
				float fx =
				    ((float)x + (float)(rand() % 128) / 128.0f) / UVIDEOMEM_W -
				    0.5f;
				float fy =
				    ((float)y + (float)(rand() % 128) / 128.0f) / UVIDEOMEM_H -
				    0.5f;
				Ray ray = CameraCast(&scene.camera, fx, fy);
				float3 tmpclr;
				PTSceneTrace(&scene, &ray, &tmpclr);
				rayclr = float3_add(rayclr, tmpclr);
			}
			rayclr = float3_scale(rayclr, 1.0f / nsamples);
			float3 curclr = float3_frompixel(vmem[UVIDEOMEM_W * y + x]);
			curclr = float3_add(float3_scale(curclr, (npass - 1.0f) / npass),
					    float3_scale(rayclr, 1.0f / npass));
			curclr = float3_clamp(curclr);
			vmem[UVIDEOMEM_W * y + x] = float3_topixel(curclr);
		}
	}
	npass++;
	goto again;
}

int main(int argc, char **argv)
{
	uvideomem_init(&upt_main);
}