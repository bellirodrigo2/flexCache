
typedef unsigned long size_fx;

typedef struct allocator_fx allocator_fx;

typedef void (*free_fx) (void*);
typedef void *(*alloc_fx)  (size_fx size);

struct allocator_fx{
    alloc_fx* alloc;
    free_fx* free;
};