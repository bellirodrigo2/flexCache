#ifndef __FLEXCACHE_H__
#define __FLEXCACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "commons.h"
#include "stack_fx.h" 

typedef struct flexcache flexcache;

enum EVICTION_POLICY{
    LRU,
    LFU,
    FIFO,
    TTL, 
    RANDOM
};

typedef struct set_option {

    bool_t        KEEPTTL; // KEEPTTL -- Retain the time to live associated with the key.
    long          EXAT; //timestamp-seconds -- Set the specified Unix time at which the key will expire, in seconds (a positive integer).
    long          PXAT; //timestamp-milliseconds -- Set the specified Unix time at which the key will expire, in milliseconds (a positive integer).

    long          EX; //seconds -- Set the specified expire time, in seconds (a positive integer).
    long          PX; //milliseconds -- Set the specified expire time, in milliseconds (a positive integer).

    bool_t        NX; // NX -- Only set the key if it does not already exist.
    bool_t        XX; // XX -- Only set the key if it already exists.


} set_option;

void fcache_init(flexcache* cache, enum EVICTION_POLICY evic_pol, data_aux_funcs_t funcs, size_t maxmemory);

void fcache_set_free(flexcache *cache, void* key, const void* value, set_option* options, free* cb_free);

stack_fx* fcache_set(flexcache *cache, void* key, const void* value, set_option* options);

bool_t fcache_key_exists(flexcache *cache, void* key);

const void* fcache_get_ptr(flexcache *cache, void* key);

void* fcache_get_copy(flexcache *cache, void* key);

void* fcache_find_any(flexcache *cache, pred* pred, void* aux_data);

stack_fx* fcache_find_all(flexcache *cache, void* key, pred* pred, void* aux_data);

#ifdef __cplusplus
}
#endif

#endif
