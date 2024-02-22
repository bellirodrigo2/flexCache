#ifndef __FNODE_H__
#define __FNODE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum node_type node_type;

typedef struct metadata_t metadata_t;

typedef struct flexnode flexnode;

flexnode* fnode_create(KEY_TYPE key, const DATA_TYPE* value, size_t len, size_t exp_seconds, allocator_t* allocator);

DATA_TYPE* fnode_destroy(flexnode* node, allocator_t* allocator);

metadata_t* fnode_get_metadata(flexnode* node);

DATA_TYPE* fnode_get_data(flexnode* node);

node_type fnode_get_type(flexnode* node);

bool_t fnode_is_volatile(flexnode* node);

#ifdef __cplusplus
}
#endif

#endif