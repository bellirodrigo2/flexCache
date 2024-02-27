#ifndef _MAP_H_
#define _MAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "com_types.h"
#include "lib/rbtree.h"
#include "flexnode.h"

typedef RBTree map_fx;

FX_INLINE void map_init(map_fx* map){
    return rbtree_init(map);
}

FX_INLINE void map_set(map_fx* map,  void* key, flexnode* value){
    return rbtree_insert(map, key, value);
}

FX_INLINE flexnode* map_get(map_fx* map,  void* key){
    return rbtree_lookup_key(map, key);
}

FX_INLINE bool_t map_contains(map_fx* map,  void* key){
    return rbtree_contains_key(map, key);
}

FX_INLINE flexnode* map_remove(map_fx* map,  void* key){
    return rbtree_remove(map, key);
}

#ifdef __cplusplus
}
#endif

#endif
