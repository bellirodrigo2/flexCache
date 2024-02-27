#ifndef __COM_TYPES_H_
#define __COM_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "allocator.h"

#define FX_INLINE inline

typedef char bool_t;

typedef struct time_fx{
    long tv_sec;
    long tv_nsec;
}time_fx;

typedef size_fx (*len_func)(void* data);
typedef void* (*copy_func)(void* data);
typedef int (*cmp_func)(const void *key1, const void *key2);
typedef void (*now_func)(time_fx*);

typedef struct data_aux_funcs_t{
    const len_func*          len_func;
    const copy_func*         copy_func;
    const cmp_func*          compare;
    
    const allocator_fx*      allocator;
    const now_func*          now;
} data_aux_funcs_t;

void swap_ptr_fx(void* a, void* b);

void memcopy_fx(void *src, const void *dest, size_fx size);

void memcopy_zer_src_fx(void *src, const void *dest, size_fx size);

void zero_mem_fx(void *mem, size_fx size);

#define NS_PER_SECOND 1000000000

void time_fx_add(time_fx t1, time_fx t2, time_fx *td);

bool_t time_fx_is_later(time_fx t1, time_fx t2);

void time_fx_add_seconds(time_fx t1, long t2, time_fx *td);

void time_fx_sub(time_fx t1, time_fx t2, time_fx *td);

#ifdef __cplusplus
}
#endif

#endif