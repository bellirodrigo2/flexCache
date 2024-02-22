#include "flexcache.h"
#include "flexnode.h"
#include "allocator.h"

struct flexcache{
    eviction_list_t    evic_list;
    map_t              kv_map;
    fcache_config      config;

};


void fcache_init(flexcache* cache, eviction_list_t* evlist, map_t* map, fcache_config *config){
    
    if(!cache, !evlist || !map || !config){
        return 0;
    }
    
    cache->evic_list = *evlist;
    cache->kv_map = *map;
    cache->config = *config;
}

struct set_return{
    bool_t    predicate;
    vector_t* removed;
};

// SE FOR POSSIVEL OVEWRITE, TEM QUE RETORNAR O DADO ANTIGO, OU ENTAO PASSAR UMA FUNCAO FREE
// PASSAR FUNCAO FREE EH COMPLICADO, POIS TEREMOS QUE HANDLE FREE DO CLIENTE DATA
vector_t* fcache_set(flexcache *cache, KEY_TYPE key, const DATA_TYPE* value, set_option* options){

    //what if options is NULL...need a STD_OPTIONS on FCACHE_CONFIG... overwrite

    vector_t* vec_removed = 0;

    bool_t exists = fcache_key_exists(cache, key); // O(log(n))
    if(exists){
        if(!options->overwrite){
            return vec_removed;
            //nulo
        } else {
            DATA_TYPE* old_value = fcache_delete(cache, key);
            vec_insert(vec_removed, old_value);
            return vec_removed;
            //old value
        }
    }

    //tem que retornar um vector de pointer pros dados removidos ?
    //como saber se go_ahead ou nao... retornar um struct ??? goahead and vec_removed
    // ai a propria funcao tem que retornar
    bool_t go_ahead = fcache_check_evict(cache, value); // worst O(n)
    if(!go_ahead){
        //retornar o old_value aqui ????????????????
        //remover do vec_removed
        //adicionar o new_value no vec_removed ??? nao faz sentido
        return vec_removed;
    }

    allocator_t *allocator = allocator;
    size_t exp_sec = options->exp_seconds;
    size_t len = (*cache->config.len_func)(value);
    
    flexnode *node = fnode_create(key, value, len, exp_sec, allocator);
    if(!node){

        //retornar o old_value aqui ????????????????
        //remover do vec_removed
        //ACHO QUE NAO TEM COMO, PQ TERIA QUE RODAR fnode_create do mesmo jeito
        return vec_removed;
    }

    //at this point, if key exists, overwrite it
    map_t* map = &cache->kv_map;
    map_set(map, key, node); //O(log(n))
    if(false){ //pelo que vi nao tem pq dar errado aqui
        fnode_destroy(node,allocator);

        //se ja checou em cima, nao tem como dar erro....
        //se der erro pode seru um codigo, bad state talvez
        // return RETURN_ERR_BAD_STATE;
        return vec_removed;
    }

    eviction_list_t* list = &cache->evic_list;
    return_code set_evic_list = eviclist_insert(list, node); //O(1)
    if(false){ //pelo que vi nao tem pq dar errado aqui
        //acho que nao tem oque dar errado aqui

        map_t* map = &cache->kv_map;
        map_delete(map, key);
        fnode_destroy(node, allocator);
        // quais erros podem acontecer aqui ???
        //LRU eh somente insert um dllist - OK
        //LFU idem
        //TTL idem
        //RANDOM eh add to vector... tem que alocar....pode dar problema...tem que fazer um alocator
        // return set_evic_list;
        return vec_removed;
    }

    //update cache items and memory usage
    if(options->isvolatile){
        cache->config.volatileitems += 1;
        cache->config.volatilememory += len;
    } else{
        cache->config.nonvolatileitems += 1;
        cache->config.nonvolatilememory += len;
    }

    return vec_removed;
}

DATA_TYPE* fcache_get(flexcache *cache, KEY_TYPE key){

    flexnode* node = map_get(&cache->kv_map, key);
    if(!node){
        //ver se ha algum erro importante aqui, ou somente retorna NULL
        //tem que retornar uma copia do objeto aqui
        return node;
    }
    evic_list_touch(cache->evic_list, key);

    return (*cache->config.copy_func)(fnode_get_data(node));
}

bool_t fcache_check_evict(flexcache *cache, const DATA_TYPE* value){

    //aqui, ver se ja esta na hr de fazer um scan completo...
    //na funcao abaixo eviclist_iter_delete_if ....tem que dar um limite de len, uma funcao len

    //a funcao tem que:
        //iterar sobre os itens
        //remover baseado no predicate -- ttl_vs_now...precisa de aux value: now()
        //retornar valor removido ----
        //checar se pode parar ou nao -- predicate valor removido acumulado vs len.... precisa de aux: len
        //fazer duas funcoes
            //uma generica ... eviclist_iter_delete_if(list, ttl_vs_now, now);
            //outra mais especifica, usando o ttl vs now e checar se len foi atingido
            //retorna valor removido acumulado

    size_t len = (*cache->config.len_func)(value);

    size_t now = now();
    size_t freq = cache->config.volatile_check_frequency;
    size_t lst_check = cache->config.last_full_volatile_check;
    eviction_list_t* list = &cache->evic_list;

    if(lst_check + freq > now){
        eviclist_full_scan_clean(list); //precisa passar now ???
    } else {
        eviclist_scan_until_clean(list, len); //precisa passar now ???
    }
    //retornar um vector de pointer de data ?
    //precisa tambem retornar se o len esta disponivel ou nao

    
}

DATA_TYPE* fcache_delete(flexcache *cache, KEY_TYPE key){

    if(!fcache_key_exists(cache, key)){
        return 0;
    }

    //remove tem que retornar o node
    eviction_list_t* list = &cache->evic_list;

    flexnode* node = map_delete(&cache->kv_map, key);
    if(!node){
        return node;
    }
    eviclist_delete(list, node);

    //falta checar se null antes de retornar
    DATA_TYPE* data =  fnode_get_data(node);

    //atualizar itens e len do cache
    size_t len = (*cache->config.len_func)(data);

    if(fnode_is_volatile(node)){
        cache->config.volatileitems -= 1;
        cache->config.volatilememory -= len;
    } else{
        cache->config.nonvolatileitems -= 1;
        cache->config.nonvolatilememory -= len;
    }

    allocator_t *allocator = allocator;
    fnode_destroy(node, allocator);

    return data;
}

