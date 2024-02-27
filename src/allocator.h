
// tem que usar allocator no node create e destroy e no vector


typedef struct allocator_fx allocator_fx;

typedef void (*free) (void*);
typedef void *(*alloc)  (size_t size);

struct allocator_fx{
    alloc* alloc;
    free* free;
};