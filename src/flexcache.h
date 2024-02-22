#ifndef __FLEXCACHE_H__
#define __FLEXCACHE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "fcache_config.h"
#include "codes_flags.h"

#include "eviction_list.h" //LRU, LFU. etc...
#include "intr_map.h" //wrapper for intrusive RBtrees

typedef struct flexcache flexcache;

typedef struct set_option {

    size_t          exp_seconds;
    bool_t          overwrite;
    bool_t          isvolatile;
    
    //REDIS OPTIONS FOR SET
    // EX seconds -- Set the specified expire time, in seconds (a positive integer).
    // PX milliseconds -- Set the specified expire time, in milliseconds (a positive integer).
    // EXAT timestamp-seconds -- Set the specified Unix time at which the key will expire, in seconds (a positive integer).
    // PXAT timestamp-milliseconds -- Set the specified Unix time at which the key will expire, in milliseconds (a positive integer).
    // NX -- Only set the key if it does not already exist.
    // XX -- Only set the key if it already exists.
    // KEEPTTL -- Retain the time to live associated with the key.
    // GET -- Return the old string stored at key, or nil if key did not exist. An error is returned and SET aborted if the value stored at key is not a string.

} set_option;

typedef struct vector_t vector_t;

void fcache_init(flexcache* cache, eviction_list_t* evlist, map_t* map, fcache_config *config);

//SE RETORNAR NULL, FOI ADICIONADO... SE RETORNAR O PROPRIO 'value', deu algum problema
// SE RETORNAR UM PTR DIFERENTE, FOI OVERWRITE, E VC DEVE HANDLE O DADO ANTIGO E ATEH FREE ELE
//FAZER UM WRAPPER, QUE JA DELETA O NODE....PARA ISSO PRECISA PASSAR UM FREE_FUNC
vector_t* fcache_set(flexcache *cache, KEY_TYPE key, const DATA_TYPE* value, set_option* options);

bool_t fcache_key_exists(flexcache *cache, KEY_TYPE key);

DATA_TYPE* fcache_get(flexcache *cache, KEY_TYPE key);

DATA_TYPE* fcache_delete(flexcache *cache, KEY_TYPE key);

bool_t fcache_check_evict(flexcache *cache, const DATA_TYPE* value);

#ifdef __cplusplus
}
#endif

#endif
