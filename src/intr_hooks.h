#ifndef __INTRUSIVE_HOOKS_H
#define __INTRUSIVE_HOOKS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lib/rbtree.h"
#include "lib/list.h"

typedef RBTreeNode map_hook_t;

typedef ListNode list_hook_t;

#ifdef __cplusplus
}
#endif

#endif 