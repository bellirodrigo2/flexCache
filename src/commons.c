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

bool_t time_fx_is_later(time_fx t1, time_fx t2){

    if(t1.tv_sec < t2.tv_sec)
        return 0;

    if(t1.tv_sec == t2.tv_sec)
        return t1.tv_nsec > t2.tv_nsec;

    return 1;
    
}

FX_INLINE void time_fx_add_seconds(time_fx t1, long t2, time_fx *td){

    td->tv_sec = t2 + t1.tv_sec;
}

void time_fx_sub(time_fx t1, time_fx t2, time_fx *td)
{
    td->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    td->tv_sec  = t2.tv_sec - t1.tv_sec;
    if (td->tv_sec > 0 && td->tv_nsec < 0)
    {
        td->tv_nsec += NS_PER_SECOND;
        td->tv_sec--;
    }
    else if (td->tv_sec < 0 && td->tv_nsec > 0)
    {
        td->tv_nsec -= NS_PER_SECOND;
        td->tv_sec++;
    }
}