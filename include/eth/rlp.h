#ifndef MINTH_RLP_H
#define MINTH_RLP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "./vector-t.h"
#include "./vector-uchar.h"
#include <assert.h>

enum minth_rlp_t_tag { MINTH_RLP_T_LIST, MINTH_RLP_T_BYTE_ARR };

struct minth_rlp_t {
    union {
        vector_rlp_t list;
        vector_uchar byte_array;
    } value;
    enum minth_rlp_t_tag tag;
};

void minth_rlp_t_init_from_string_range(struct minth_rlp_t* t, const char* rlp_str_b, const char* rlp_str_e);

/***/

void minth_rlp_t_init_list(struct minth_rlp_t* t) {
    vector_rlp_t_init(&t->value.list);
    t->tag = MINTH_RLP_T_LIST;
}

void minth_rlp_t_init_list_empty(struct minth_rlp_t* t) {
    vector_rlp_t_init(&t->value.list);
    t->tag = MINTH_RLP_T_LIST;
}

void minth_rlp_t_init_byte_array_empty(struct minth_rlp_t* t) {
    vector_uchar_init(&t->value.byte_array);
    t->tag = MINTH_RLP_T_BYTE_ARR;
}

void minth_rlp_t_init_byte_array_range(struct minth_rlp_t* t, const unsigned char* first, const unsigned char* last) {
    vector_uchar_init_range(&t->value.byte_array, first, last);
    t->tag = MINTH_RLP_T_BYTE_ARR;
}

void minth_rlp_t_init_from_string(struct minth_rlp_t* t, const char* rlp_str) {
    const char* rlp_str_begin = rlp_str;
    for(; *rlp_str; ++rlp_str) {
        
    }
    minth_rlp_t_init_from_string_range(t, rlp_str_begin, rlp_str);
}

void minth_rlp_t_init_from_string_range(struct minth_rlp_t* t, const char* rlp_str_b, const char* rlp_str_e) {
    //Check if we have a list!
    if(*rlp_str_b == '[') {
        //We have an empty list if it's just 1 space apart.
        if(rlp_str_e - rlp_str_b == 1) {
            //Assert the end, just for checking
            assert(*rlp_str_e == ']');
            minth_rlp_t_init_list_empty(t);
        } else {
        
        
        
        }
    //Check if we have a byte array!
    } else if(*rlp_str_b == '0') {
        //Assert 0x prefix
        assert(*(rlp_str_b + 1) == 'x');
        if(rlp_str_e - rlp_str_b == 1) {
            //An empty byte array, if just 0x!
            minth_rlp_t_init_byte_array_empty(t);
        } else {
        
        
        
        }
    }
}

#ifdef __cplusplus
}
#endif

#endif
