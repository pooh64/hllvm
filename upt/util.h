#pragma once
#include <assert.h>
#include <stdlib.h>

static inline float rand_uniform()
{
	return rand() / (float)RAND_MAX;
}

static inline void *xmalloc(size_t size)
{
	void *ptr = malloc(size);
	assert(ptr);
	return ptr;
}