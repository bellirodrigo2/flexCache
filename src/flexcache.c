#include "flexcache.h"
#include "flexnode.h"
#include "allocator.h"
#include "fcache_config.h"
#include "wrap_dllist.h" //wrapper for intrusive double linked list
#include "wrap_map.h" //wrapper for intrusive RBtrees


//fazer duas lists.... uma volatile e outra allkeys
//allkeys eh FIFO,...touch faz nada
struct flexcache{
    dllist_fx       evic_list;
    dllist_touch*   touch;
    map_fx          kv_map;
    fcache_config   config;

};

void fcache_init(flexcache* cache, enum EVICTION_POLICY evic_pol, data_aux_funcs_t funcs, size_fx maxmemory){
    
}

static void fcache_clear_removed_list_call_cb(dllist_fx* removed_list, free_fx* cb_free){
    
    flexnode* iter = dllist_iter(list);

    while(iter!= 0){
        //- REMOVE-LOS DO MAP
        // ATUALIZAR MEMORY SIZE DO CACHE
        // E FREE OS NODES
        //CALL CB ON DATA

        iter = dllist_next(iter);
    }
    dllist_free(removed_list);

}

static void fcache_clear_removed_list_to_stack(dllist_fx* removed_list, stack_fx* vec_removed){
    
    flexnode* iter = dllist_iter(list);

    while(iter!= 0){
        //- REMOVE-LOS DO MAP
        // ATUALIZAR MEMORY SIZE DO CACHE
        // E FREE OS NODES
        //ADDICIONAR AO STCK_REMOVED

        iter = dllist_next(iter);
    }
    dllist_free(removed_list);

}

static FX_INLINE size_fx fcache_volatile_memory(flexcache *cache){
    return cache->config.volatile_memory;
}

static FX_INLINE size_fx fcache_volatile_frequency(flexcache *cache){
    return cache->config.volatile_memory;
}

static FX_INLINE time_fx fcache_last_check(flexcache *cache){
    return cache->config.volatile_memory;
}

static FX_INLINE bool_t fcache_is_check_time(time_fx now){

        size_fx freq = fcache_volatile_frequency(cache);
        time_fx lst_check = fcache_last_check(cache);
        time_fx due_time;

        time_fx_add_seconds(lst_check, freq, &due_time);

        return time_fx_is_later(now, due_time);
}

static void fcache_check_evict(flexcache *cache, const flexnode* node, dllist_fx* removed_list){

    eviction_list_t* list = &cache->evic_list;

    time_fx now;
    cache.funcs.now(&now);

    if(fcache_is_check_time(now)){
        dllist_fx* new_removed = dllist_full_scan_clean(list, now);
        dllist_concat(removed_list, new_removed);
    }

    size_fx len = fnode_get_size(node);
    size_fx available = fcache_available_volatile_memory(cache);
    if(len > available){
        dllist_fx* new_removed = dllist_scan_clean_until(list, len - available);
        dllist_concat(removed_list, new_removed);
    }
}

static dllist_fx* set_internal(flexcache *cache, void* key, const void* value, set_option* options){
    
    map_fx* map = &cache->kv_map;  
    eviction_list_t* list = &cache->evic_list;
    allocator_fx* allocator = cache->config.funcs.allocator;
    len_func* length = cache->config.funcs.len_func;
    //CALCULAR O TTL
    //O NODE TEM QUE TER O END TIME APENAS
    // size_fx EX = options->EX;

    size_fx data_size = (*length)(value);
    size_fx vol_memory = fcache_volatile_memory(cache);

    dllist_fx removed_list;
    flexnode* existing_node = map_get(map, key);
    if(!existing_node){
        if(options->XX)
            return 0;
        if(data_size > vol_memory)
            return 0;
    } else {
        if(options->NX)
            return 0;
        
        size_fx old_size = fnode_get_size(existing_node);
        if(data_size > old_size + vol_memory)
            return 0;

        if(options->KEEPTTL)
            size_fx TTL = fnode_get_ttl(existing_node);
            //SETAR OPTIONS EXAT e PXAT

        
        flexnode* old_node = fcache_remove_internal(cache, key);
        if(old_node)
            dllist_insert(&removed_list, old_node);
    }

    flexnode *node;
    fnode_init(node, key, value, data_size, options);
    fcache_check_evict(cache, node, &removed_list); // worst O(n)

    map_set(map, key, node); //O(log(n))
    dllist_insert(list, node); //O(1)

    //update cache items and memory usage
    if(fnode_is_volatile(node)){
        cache->config.volatilememory += data_size;
    } else{
        cache->config.nonvolatilememory += data_size;
    }

    return &removed_list;
}

FX_INLINE stack_fx* fcache_set(flexcache *cache, void* key, const void* value, set_option* options){
    
    allocator_fx* allocator = cache->config.funcs.allocator;

    dllist_fx* removed_list = fcache_set_internal(cache, key, value, options);
    stack_fx* removed = 0;
    stack_init(removed, allocator.alloc);
    fcache_clear_removed_list_to_stack(removed_list, removed);

    return removed;
}

void fcache_set_free(flexcache *cache, void* key, const void* value, set_option* options, free_fx* cb_free){

    dllist_fx* removed_list = fcache_set_internal(cache, key, value, options);
    fcache_clear_removed_list_call_cb(removed_list, cb_free);

}

const void* fcache_get_ptr(flexcache *cache, void* key){

    map_fx* map = &cache->kv_map;  
    eviction_list_t* list = &cache->evic_list;

    flexnode* node = map_get(map, key);
    if(!node){
        return node;
    }

    dllist_touch* touch = cache->touch;
    touch(list, node);

    const void* data = fnode_get_data(node);
    return data;
}

FX_INLINE void* fcache_get_copy(flexcache *cache, void* key){

    void* data = fcache_get_ptr(cache, key);
    const copy_func* copy = cache->config.funcs.copy_func;
    return (*copy)(data);
}

static flexnode* fcache_remove_internal(flexcache *cache, void* key){
    
    if(!map_contains(cache, key)){
        return 0;
    }

    eviction_list_t* list = &cache->evic_list;
    allocator_fx *allocator = allocator;
    const len_func* length = cache->config.funcs.len_func;

    flexnode* node = map_remove(&cache->kv_map, key);
    if(!node){
        return node;
    }
    dllist_remove(list, node);

    void* data = fnode_get_data(node);
    size_fx len = (*length)(data);

    if(fnode_is_volatile(node)){
        cache->config.volatilememory -= len;
    } else{
        cache->config.nonvolatilememory -= len;
    }

    return node;
}

void* fcache_remove(flexcache *cache, void* key){
    
    allocator_fx *allocator = allocator;

    flexnode* node = fcache_remove_internal(cache, key);
    void* data = fnode_get_data(node);

    // fnode_destroy(node, allocator);
    allocator->free_fx(node);

    return data;
}   