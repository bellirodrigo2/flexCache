#include "stack_fx.h"

#define DEFAULT_CAPACITY 8
#define DEFAULT_EXPANSION_FACTOR 2

#define CC_MAX_ELEMENTS ((size_t) - 2)

struct stack_fx{
    size_t          size;
    size_t          capacity;
    void**          buffer;
    allocator_fx   allocator;
};

void stack_init(stack_fx* stck, allocator_fx* alloc){

    stck = (*alloc->alloc)(sizeof(stack_fx));
    if (!stck)
        return;

    stck->size = 0;
    stck->capacity = 0;
    stck->buffer = 0;
    stck->allocator = *alloc;
}

static int expand_capacity(stack_fx* stck){

    if (stck->capacity == CC_MAX_ELEMENTS)
        return 0;

    size_t new_capacity = (size_t)(stck->capacity * DEFAULT_EXPANSION_FACTOR);

    if (new_capacity <= stck->capacity)
        new_capacity = CC_MAX_ELEMENTS;

    void **new_buff = (*stck->allocator.alloc)(new_capacity * sizeof(void*)); 
    if (!new_buff)
        return 0;

    memcpy_fx(new_buff, stck->buffer, stck->size * sizeof(void*));
    // memcopy_zer_src_fx(new_buff, stck->buffer, stck->size * sizeof(void*)); //need zero old buffer ??

    (*stck->allocator.free)(stck->buffer);
    stck->buffer = new_buff;
    stck->capacity = new_capacity;


    return 1;
}

int stack_push(stack_fx* stck, void *element){

    if(stck->size == 0){
        stck->buffer = (*stck->allocator.alloc)(DEFAULT_CAPACITY * sizeof(void*));
        if (!stck->buffer)
            return 0;

        // zero_mem_fx(stck->buffer, DEFAULT_CAPACITY); //need zero new buffer ?
        stck->capacity = DEFAULT_CAPACITY;
    }

    if (stck->size >= stck->capacity) {
        int status = expand_capacity(stck);
        if (status == 0)
            return status;
    }

    stck->buffer[stck->size] = element;
    stck->size++;

    return 1;
}

void* stack_pop(stack_fx* stck){

    if (stck->size == 0){
        (*stck->allocator.free)(stck);
        return 0;
    }

    void* tgt = 0;
    swap_ptr_fx(stck->buffer[stck->size], tgt);

    stck->size--;

    if (stck->size == 0){
        (*stck->allocator.free)(stck->buffer);
        stck->buffer = 0;
    }

    return tgt;
}