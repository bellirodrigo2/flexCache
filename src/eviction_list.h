#ifndef _EVICTION_LISTS_H_
#define _EVICTION_LISTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "flexnode.h"
#include "codes_flags.h"

typedef enum eviction_policy_t{
    NO_EVICTION =  0,
    LRU_EVICTION = 1,
    LFU_EVICTION = 2,
    RANDOM_EVICTION = 3,
    TTL_EVICTION = 4

} eviction_policy_t;

typedef enum volatility_t{
    ALLKEYS = 0,
    VOLATILE = 1
} volatility_t;


//colocar no eviction list as funcoes abaixo e mais o struct abaixo generico...
//LRU eh dlinked list - head, tail OK
//lfu eh dlinked list - head, tail OK
//ttl eh dlinked list - head, tail OK
//random eh vector - fazer head apenas, tail eh null - OK

typedef struct eviction_list_t {
    flexnode *head;
    flexnode *tail;
    int size;
    //COLOCAR FUNCOES AQUI...CADA TIPO (LRU, LFU, etc) TEM SUAS FUNCOES DIFERENTES
} eviction_list_t;

typedef bool_t (*predicate)(flexnode* node, void* aux_data);

return_code eviclist_init(eviction_list_t* list);

static bool_t ttl_vs_now(flexnode* node, void* aux_data){

    return 0;
}

// PENSAR BEM AQUI.............. EVICLIST TEM QUE SABER QUAL EH O NODE
// ADICIONAR UMA DEPENDENCIA DO FLEXNODE AQUI

return_code eviclist_insert(eviction_list_t* list, flexnode* node);


void eviclist_iter_delete_if(eviction_list_t* list, predicate, void* aux_data);

return_code eviclist_touch(eviction_list_t* list, flexnode* node);
return_code eviclist_delete(eviction_list_t* list, flexnode* node);

#ifdef __cplusplus
}
#endif

#endif
