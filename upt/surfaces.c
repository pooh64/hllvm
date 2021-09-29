#include "upt/surfaces.h"
#include "upt/float3.h"
#include <math.h>
#include <stdlib.h>

DEF_MATERIAL_APPLY(Mirror)
{
	Ray refl = {.o = RayAt(hit->ray, hit->t), .d = float3_refl(hit->ray.d, hit->sn)};
	hit->ray = refl;
	*color = float3_mul(*color, this->color);
	return true;
}

DEF_MATERIAL_APPLY(Lamp)
{
	float cosine = -float3_dot(hit->sn, hit->ray.d);
	*color = float3_scale(*color, 0.4 + 0.6 * cosine);
	*color = float3_mul(*color, this->color);
	return false;
}

static inline void BuildONB(float3 const *n, float3 *u, float3 *v)
{
	float tmp = rsqrtf(n->x * n->x + n->y * n->y);
	*u = (float3){n->y * tmp, -n->x * tmp, 0};
	*v = float3_cross(*u, *n);
}

DEF_MATERIAL_APPLY(Lambert)
{
	float3 u, v;
	BuildONB(&hit->sn, &u, &v);

	float phi = 2.0f * M_PI * rand_uniform();
	float r = sqrtf(rand_uniform());
	float x = r * cosf(phi);
	float y = r * sinf(phi);
	float z = sqrtf(1 - x * x - y * y);

	hit->ray.o = RayAt(hit->ray, hit->t);
	hit->ray.d = float3_add(float3_add(float3_scale(u, x), float3_scale(v, y)),
				float3_scale(hit->sn, z));
	*color = float3_mul(*color, this->color);
	return true;
}

DEF_MATERIAL_APPLY(Phong)
{
	float phi = 2.0f * M_PI * rand_uniform();
	float cost = powf(1 - rand_uniform(), 1.0f / (this->pexp + 1));
	float sint = sqrtf(1 - cost * cost);
	float x = cosf(phi) * sint;
	float y = sinf(phi) * sint;
	float z = cost;

	float3 u, v;
	float3 w =
	    float3_sub(hit->ray.d, float3_scale(hit->sn, 2.0f * float3_dot(hit->ray.d, hit->sn)));
	BuildONB(&w, &u, &v);
	hit->ray.o = RayAt(hit->ray, hit->t);
	hit->ray.d =
	    float3_add(float3_add(float3_scale(u, x), float3_scale(v, y)), float3_scale(w, z));

	*color = float3_mul(*color, this->color);
	return float3_dot(hit->ray.d, w) > 0.0f;
}

DEF_MATERIAL_APPLY(Glass)
{
	float const np = 1.5f;
	float3 trm;

	float cosine = float3_dot(hit->ray.d, hit->sn);
	if (cosine < 0.0f) {
		cosine = -cosine;
		float tmp = 1.0f / np;
		float sq = 1.0f - (tmp * tmp) * (1.0f - cosine * cosine);
		trm = float3_add(float3_scale(hit->ray.d, tmp),
				 float3_scale(hit->sn, (tmp * cosine - sqrtf(sq))));
	} else {
		float tmp = float3_dot(hit->ray.d, hit->sn);
		float sq = 1.0f - (np * np) * (1 - tmp * tmp);
		if (sq < 0) {
			*color = (float3){0.0f, 0.0f, 0.0f};
			return false;
		}
		trm = float3_sub(float3_scale(hit->ray.d, np),
				 float3_scale(hit->sn, (np * tmp - sqrtf(sq))));
	}

	hit->ray.o = RayAt(hit->ray, hit->t);
	hit->ray.d = trm;
	*color = float3_mul(*color, this->color);
	return true;
}