
// tem que usar allocator no node create e destroy e no vector

typedef struct allocator_t{
    void *(*mem_alloc)  (size_t size);
    void *(*mem_calloc) (size_t blocks, size_t size);
    void  (*mem_free)   (void *block);
} allocator_t;