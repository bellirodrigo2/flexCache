
#include "flexnode.h"
#include "intrusive_hooks.h"

enum node_type {
    SINGLE,
    LIST,
    MAP
};

struct metadata_t{
    size_t      size;
    time_t      epoch; //timestamp
    time_t      lst_used;
    long        exp_seconds; //non volatile is -1 ----ISSO EH IMPORTANTE
    long        times_used;
    node_type   type;
};

struct flexnode{
    map_hook_t      map_hook;
    list_hook_t     list_hook;
    metadata_t      meta;
    DATA_TYPE*      data;
    KEY_TYPE        key;
};