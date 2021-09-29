#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define UVIDEOMEM_W (1560u)
#define UVIDEOMEM_H (1024u)
extern uint32_t volatile *uvideomem;
void uvideomem_init(void (*fn)());

#ifdef __cplusplus
}
#endif