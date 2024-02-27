#ifndef _DLLIST_H_
#define _DLLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/list.h"
#include "flexnode.h"

typedef List dllist_t;

typedef ListNode dllist_node_t;


typedef void (*dllist_touch)(eviction_list_fx* list, flexnode* node);


void dllist_init(dllist_t* list);

FX_INLINE void dllist_insert(dllist_t* dllist, dllist_node_t* node){
    return list_insert_front(dllist, node);
}

FX_INLINE void dllist_concat(dllist_t* dllist1, dllist_t* dllist2){
    return;
}

void dllist_remove(eviction_list_fx* list, flexnode* node);

flexnode* dllist_iter(eviction_list_fx* list);

flexnode* dllist_next(flexnode* iter);

dllist_fx dllist_full_scan_clean(eviction_list_fx* list, size_t now);

dllist_fx dllist_scan_clean_until(eviction_list_fx* list, size_t until);

void dllist_touch_LRU(eviction_list_fx* list, flexnode* node);

void dllist_touch_LFU(eviction_list_fx* list, flexnode* node);

void dllist_touch_TTL(eviction_list_fx* list, flexnode* node);

void dllist_touch_FIFO(eviction_list_fx* list, flexnode* node);

void dllist_touch_RANDOM(eviction_list_fx* list, flexnode* node);

#ifdef __cplusplus
}
#endif

#endif
