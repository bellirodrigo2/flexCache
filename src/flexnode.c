
#include "flexnode.h"
#include "intr_hooks.h"

struct flexnode{
    map_hook_t      map_hook;
    list_hook_t     list_hook;
    metadata_t      meta;
    void*           data;
    void*           key;
};