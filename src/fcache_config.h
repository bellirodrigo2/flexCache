#ifndef __FCACHE_CONFIG_H__
#define __FCACHE_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef KEY_TYPE
    #define KEY_TYPE const char*
#endif

#ifndef DATA_TYPE
    #define DATA_TYPE void
#endif

typedef unsigned long size_t;
typedef char bool_t;

typedef size_t (*len_func)(DATA_TYPE* data);
typedef DATA_TYPE* (*copy_func)(DATA_TYPE* data);

typedef struct fcache_config{

    // const eviction_policy_t  eviction;
    // const volatility_t       volatility;

    const len_func*          len_func;
    const copy_func*         copy_func;
    const allocator_t*       allocator;

    size_t                   maxmemory;
    // size_t                   usedmemory;

    size_t                   volatileitems;
    size_t                   volatilememory;
    size_t                   nonvolatileitems;
    size_t                   nonvolatilememory;

    size_t                   volatile_check_frequency;
    size_t                   last_full_volatile_check;

} fcache_config;

/*
#ifndef STD_EVICTION_POLICY
    #define STD_EVICTION_POLICY LRU_EVICTION
#endif

#ifndef STD_VOLATILITY
    #define STD_VOLATILITY VOLATILE
#endif
*/

#ifdef __cplusplus
}
#endif

#endif