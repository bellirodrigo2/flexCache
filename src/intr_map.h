#ifndef _MAP_H_
#define _MAP_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct map_t {
    
} map_t;

flexnode* map_set(map_t* map,  KEY_TYPE key, const flexnode* value);

flexnode* map_get(map_t* map,  KEY_TYPE key);

flexnode* map_delete(map_t* map,  KEY_TYPE key);

#ifdef __cplusplus
}
#endif

#endif
