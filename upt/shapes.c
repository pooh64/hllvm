#include "upt/shapes.h"

bool SphereHit(Sphere *this, HitRecord *hit, float tmin, float tmax)
{
	Ray ray = hit->ray;
	float3 tmp = float3_sub(ray.o, this->o);
	float a = float3_dot(ray.d, ray.d);
	float b = 2.0f * float3_dot(ray.d, tmp);
	float c = float3_dot(tmp, tmp) - this->r * this->r;
	float discr = b * b - 4.0f * a * c;
	if (discr < 0.0f)
		return false;
	discr = sqrt(discr);
	float t = (-b - discr) / (2.0f * a);
	if (t < tmin)
		t = (-b + discr) / (2.0f * a);
	if (t < tmin || t > tmax)
		return false;
	hit->t = t;
	hit->sn = float3_norm(float3_sub(RayAt(ray, t), this->o));
	hit->material = this->material;
	return true;
}