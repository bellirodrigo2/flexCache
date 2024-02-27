#ifndef __FCACHE_CONFIG_H__
#define __FCACHE_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "com_types.h"

typedef struct fcache_config fcache_config;

struct fcache_config{

    data_aux_funcs_t         funcs;

    size_t                   maxmemory;

    size_t                   volatilememory;
    size_t                   nonvolatilememory;

    size_t                   volatile_check_frequency;
    time_fx                   last_full_volatile_check;

};

#ifdef __cplusplus
}
#endif

#endif