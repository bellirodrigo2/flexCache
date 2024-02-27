
#ifndef STACK_FX_H
#define STACK_FX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "com_types.h"

typedef struct stack_fx stack_fx;

void stack_init(stack_fx* stack, allocator_fx* alloc);

int stack_push(stack_fx* stck, void *element);

void* stack_pop(stack_fx* stck);

#ifdef __cplusplus
}
#endif

#endif 
