#include "../../include/eth/rlp.h"
#include "../../include/eth/vector-rlp-t.h"
#include <stdio.h>
#include <string.h>
/*
int main() {
    vector_rlp_t list;
    vector_rlp_t_init(&list);
    printf("OwO: %lu\n", vector_rlp_t_capacity(&list));
    printf("\n\n");
    struct minth_rlp_t rlp;
    minth_rlp_t_init_from_string(&rlp, "0x");
    minth_rlp_t_init_from_string(&rlp, "0xA291");
    minth_rlp_t_init_from_string(&rlp, "[]");
    minth_rlp_t_init_from_string(&rlp, "[[[[]]]]");
    minth_rlp_t_init_from_string(&rlp, "[0xA393,0x00]");
    minth_rlp_t_init_from_string(&rlp, "[0xA393,[],[]]");
    minth_rlp_t_init_from_string(&rlp, "[0xA393,0x843CAB[],[[]]],0xFF]");
}
*/
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

void minth_rlp_t_init_byte_array_hexstring(struct minth_rlp_t* t, const char* first, const char* last) {
    //Calculate amount of space needed and initialize
    //This is probably a better fit for a function of vector_uchar
    size_t sz = ceil(((double)(last-first)/2));
    vector_uchar_init_size(&t->value.byte_array, sz);
    memset(t->value.byte_array.head, 0, sz);
    minth_util_hexstringtobytes(t->value.byte_array.head, first, last);
    t->tag = MINTH_RLP_T_BYTE_ARR;
}

void minth_rlp_t_init_from_string(struct minth_rlp_t* t, const char* rlp_str) {
    const char* rlp_str_begin = rlp_str;
    for(; *rlp_str; ++rlp_str)
        ;
    minth_rlp_t_init_from_string_range(t, rlp_str_begin, rlp_str);
}

void minth_rlp_t_init_from_string_range(struct minth_rlp_t* t, const char* rlp_str_b, const char* rlp_str_e) {
    //Check if we have a list!
    if(*rlp_str_b == '[') {
        //We have an empty list if it's just []
        if(rlp_str_e - rlp_str_b == 2) {
            //Assert the end, just for checking
            assert(*(rlp_str_e - 1) == ']');
            minth_rlp_t_init_list_empty(t);
        } else {
            //Work through each T in the list and recurse~ λ 
            //NOTE: It might be neat to get the number of commas to know how much
            //space to reserve! Just saying.
            minth_rlp_t_init_list(t);
            ++rlp_str_b;
            const char* comm;
            const char* space;
            struct minth_rlp_t e;
            for(;; rlp_str_b = comm + 1) {
                algorithm_find(rlp_str_b, rlp_str_e, ',', comm);
                if(comm == rlp_str_e) {
                    //No more commas to zoom through! No more elements in the list, break!
                    break;
                }
                //Advance to first non-space
                for(; *rlp_str_b == ' '; ++rlp_str_b)
                    ;
                //Look for first non-space character to end, and parse!
                algorithm_find(rlp_str_b, comm, ' ', space);
                //We have a valid range [rlp_str_b, space), so:
                minth_rlp_t_init_from_string_range(&e, rlp_str_b, space);
                vector_rlp_t_push_back(&t->value.list, e);
                
            }
            //No commas, but we still have one element regardless: 
            //Advance to first non-space
            for(; *rlp_str_b == ' '; ++rlp_str_b)
                ;
            //Look for first non-space character to end, and parse!
            //ASSUMPTION: rlp_str_e - 1 is ']'
            algorithm_find(rlp_str_b, rlp_str_e - 1, ' ', space);
            //We have a valid range [rlp_str_b, space), so:
            minth_rlp_t_init_from_string_range(&e, rlp_str_b, space);
            vector_rlp_t_push_back(&t->value.list, e);
        }
    //Check if we have a byte array!
    } else if(*rlp_str_b == '0') {
        //Assert 0x prefix
        assert(*(rlp_str_b + 1) == 'x');
        if(rlp_str_e - rlp_str_b == 1) {
            //An empty byte array, if just 0x!
            minth_rlp_t_init_byte_array_empty(t);
        } else {
            //Note: This will break if last element is not part of the byte array! i.e. spaces,
            //assume that each call is sanitized in terms of whitespace.
            minth_rlp_t_init_byte_array_hexstring(t, rlp_str_b + 2, rlp_str_e);
        }
    }
}

/* TODO: Finish
void minth_rlp_t_deinit(struct minth_rlp_t* t) {

}
*/
