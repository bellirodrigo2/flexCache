#ifndef __FNODE_H__
#define __FNODE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "com_types.h"
#include "flexcache.h"

typedef enum node_type node_type;

typedef struct metadata_t metadata_t;

enum node_type {
    SINGLE,
    LIST,
    MAP
};

struct metadata_t{
    const size_t             size;
    const time_fx             epoch; //timestamp
    time_fx                   lst_used;
    long                     exp_seconds; //non volatile is -1 ----ISSO EH IMPORTANTE
    long                     times_used;
    const enum node_type     type;
};

typedef struct flexnode flexnode;

void fnode_init(flexnode* node, void* key, const void* value, size_t len, set_option options);

void* fnode_destroy(flexnode* node, allocator_t* allocator);

metadata_t* fnode_get_metadata(flexnode* node);

size_t fnode_get_size(flexnode* node);

const void* fnode_get_data(flexnode* node);

long fnode_get_ttl(flexnode* node);

node_type fnode_get_type(flexnode* node);

bool_t fnode_is_volatile(flexnode* node);

#ifdef __cplusplus
}
#endif

#endif