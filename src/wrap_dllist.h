#ifndef _DLLIST_H_
#define _DLLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/list.h"
#include "flexnode.h"

typedef List dllist_fx;

typedef ListNode dllist_node_fx;


typedef void (*dllist_touch)(dllist_fx* list, flexnode* node);


void dllist_init(dllist_fx* list);

FX_INLINE void dllist_insert(dllist_fx* dllist, dllist_node_fx* node){
    return list_insert_front(dllist, node);
}

FX_INLINE void dllist_concat(dllist_fx* dllist1, dllist_fx* dllist2){
    return;
}

void dllist_remove(dllist_fx* list, flexnode* node);

flexnode* dllist_iter(dllist_fx* list);

flexnode* dllist_next(flexnode* iter);

dllist_fx dllist_full_scan_clean(dllist_fx* list, size_t now);

dllist_fx dllist_scan_clean_until(dllist_fx* list, size_t until);

void dllist_touch_LRU(dllist_fx* list, flexnode* node);

void dllist_touch_LFU(dllist_fx* list, flexnode* node);

void dllist_touch_TTL(dllist_fx* list, flexnode* node);

void dllist_touch_FIFO(dllist_fx* list, flexnode* node);

void dllist_touch_RANDOM(dllist_fx* list, flexnode* node);

#ifdef __cplusplus
}
#endif

#endif
