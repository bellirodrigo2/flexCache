#ifndef _CODES_FLAGS_H_
#define _CODES_FLAGS_H_


#ifdef __cplusplus
extern "C" {
#endif

typedef enum return_code{
    
    // DATA STRUCTURE CODES
    RETURN_OK                           = 0,
    RETURN_ERR_ALLOC                    = 1,
    RETURN_ERR_INVALID_CAPACITY         = 2,
    RETURN_ERR_INVALID_RANGE            = 3,
    RETURN_ERR_MAX_CAPACITY             = 4,
    RETURN_ERR_KEY_NOT_FOUND            = 6,
    RETURN_ERR_VALUE_NOT_FOUND          = 8,
    RETURN_ERR_OUT_OF_RANGE             = 9,
    RETURN_ITER_END                     = 10,

    // CACHE CODES
    RETURN_ERR_NO_MEMORY                = 11,
    RETURN_ERR_KEY_EXISTS_NO_OVERWRITE  = 12,
    RETURN_ERR_BAD_STATE                = 13

} return_code;

#ifdef __cplusplus
}
#endif

#endif