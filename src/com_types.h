#ifndef __COM_TYPES_H_
#define __COM_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "allocator.h"

#define FX_INLINE inline

typedef unsigned long size_t;
typedef char bool_t;

typedef struct time_fx{
    long tv_sec
    long int tv_nsec
}time_fx;

typedef size_t (*len_func)(void* data);
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

FX_INLINE void swap_ptr_fx(void* a, void* b){
    void* tmp = a;
    a = b;
    b = tmp;
}

FX_INLINE void memcopy_fx(void *src, const void *dest, size_t size){
    char *csrc = (char *)src;  
    char *cdest = (char *)dest;  
  
    for (size_t i = 0; i < size; i++)
        cdest[i] = csrc[i];
}

FX_INLINE void memcopy_zer_src_fx(void *src, const void *dest, size_t size){
    char *csrc = (char *)src;  
    char *cdest = (char *)dest;  
  
    for (size_t i = 0; i < size; i++)
        cdest[i] = csrc[i];
        csrc[i] = 0;
}

FX_INLINE void zero_mem_fx(void *mem, size_t size){
  
    for (size_t i = 0; i < size; i++)
        mem[i] = 0;
}

#define NS_PER_SECOND 1000000000

void time_fx_add(time_fx t1, time_fx t2, time_fx *td){

    long sec = t2.tv_sec + t1.tv_sec;
    long nsec = t2.tv_nsec + t1.tv_nsec;

    // CHECK LONG OVERFLOW ???????

    if (nsec >= NS_PER_SECOND) {
        nsec -= NS_PER_SECOND;
        sec++;
    }

    td->tv_sec = sec;
    td->tv_nsec = nsec;
}

bool_t time_fx_is_later(time_fx t1, time_fx t2){

    if(t1.tv_sec < t2.tv_sec)
        return 0;

    if(t1.tv_sec == t2.tv_sec)
        return t1.tv_nsec > t2.tv_nsec;

    return 1;
    
}

FX_INLINE void time_fx_add_seconds(time_fx t1, long t2, time_fx *td){

    td->tv_sec = t2 + t1.tv_sec;
}

void time_fx_sub(time_fx t1, time_fx t2, time_fx *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}

#ifdef __cplusplus
}
#endif

#endif