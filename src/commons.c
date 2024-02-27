#include "commons.h"

void swap_ptr_fx(void* a, void* b){
    void* tmp = a;
    a = b;
    b = tmp;
}
void memcopy_fx(void *src, const void *dest, size_fx size){
    char *csrc = (char *)src;  
    char *cdest = (char *)dest;  
  
    for (size_fx i = 0; i < size; i++)
        cdest[i] = csrc[i];
}

void memcopy_zer_src_fx(void *src, const void *dest, size_fx size){
    char *csrc = (char *)src;  
    char *cdest = (char *)dest;  
  
    for (size_fx i = 0; i < size; i++){
        cdest[i] = csrc[i];
        csrc[i] = 0;
    }

}

void zero_mem_fx(void *mem, size_fx size){
    
    char *mem_c = (char *)mem;  
    
    for (size_fx i = 0; i < size; i++)
        mem_c[i] = 0;
}


void time_fx_add(time_fx t1, time_fx t2, time_fx *td){

    long sec = t2.tv_sec + t1.tv_sec;
    long nsec = t2.tv_nsec + t1.tv_nsec;

    // CHECK LONG OVERFLOW ???????

    if (nsec >= NS_PER_SECOND) {
        nsec -= NS_PER_SECOND;
        sec++;
    }

    td->tv_sec = sec;
    td->tv_nsec = nsec;
}
