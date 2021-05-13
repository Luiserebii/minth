#ifndef MINTH_RLP_H
#define MINTH_RLP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "./vector-t.h"
#include "./vector-uchar.h"

enum minth_t_tag { MINTH_T_VECTOR_LIST, MINTH_T_BYTE_ARR };

struct T {
    union {
        vector_t list;
        vector_uchar byte_array;
    } value;
    enum minth_t_tag tag;
};

#ifdef __cplusplus
}
#endif

#endif
