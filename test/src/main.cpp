#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <string.h>
#include "../../include/eth/vector-rlp-t.h"
#include "../../include/eth/rlp.h"

TEST_CASE("ETH Private Key Generation", "[meme]") {
    REQUIRE(1 == 1);

}
void print_uchar_arr(const unsigned char* arr, size_t sz) {
    for(size_t i = 0; i < sz; ++i) {
        printf("%x", arr[i]);
    }
    putchar('\n');
}

TEST_CASE("Testing Struct RLP_T", "[rlp_t]") {
    struct minth_rlp_t rlp;

    SECTION("0x (empty byte array)") {
        minth_rlp_t_init_from_string(&rlp, "0x");

        REQUIRE(rlp.tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&rlp.value.byte_array) == 0);
    }

    SECTION("0xA291 (a valid byte array)") {
        minth_rlp_t_init_from_string(&rlp, "0xA291");
        unsigned char b[2] = {0xA2, 0x91};

        REQUIRE(rlp.tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&rlp.value.byte_array) == 2);
        REQUIRE(memcmp(vector_uchar_begin(&rlp.value.byte_array), b, 2) == 0);
    }

    SECTION("[] (empty list)") {
        minth_rlp_t_init_from_string(&rlp, "[]");

        REQUIRE(rlp.tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&rlp.value.list) == 0);
    }

    SECTION("[[[]]] (nested lists)") {
        minth_rlp_t_init_from_string(&rlp, "[[[]]]");

        REQUIRE(rlp.tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&rlp.value.list) == 1);

        struct minth_rlp_t* e = vector_rlp_t_begin(&rlp.value.list);
        REQUIRE(e->tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&e->value.list) == 1);

        e = vector_rlp_t_begin(&e->value.list);
        REQUIRE(e->tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&e->value.list) == 0);
    }

    SECTION("[0xA393,0x5CEC20DB,0x00]") {
        minth_rlp_t_init_from_string(&rlp, "[0xA393,0x5CEC20DB,0x00]");

        REQUIRE(rlp.tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&rlp.value.list) == 3);

        unsigned char ba1[] = {0xA3, 0x93};
        struct minth_rlp_t* e = vector_rlp_t_begin(&rlp.value.list);
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 2);
        REQUIRE(memcmp(vector_uchar_begin(&e->value.byte_array), ba1, 2) == 0);

        unsigned char ba2[] = {0x5C, 0xEC, 0x20, 0xDB};
        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 4);
        REQUIRE(memcmp(vector_uchar_begin(&e->value.byte_array), ba2, 4) == 0);

        unsigned char ba3[] = {0x00};
        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 1);
        REQUIRE(memcmp(vector_uchar_begin(&e->value.byte_array), ba3, 1) == 0);

    }

    SECTION("[0xBA95,[],[]]") {
        minth_rlp_t_init_from_string(&rlp, "[0xBA95,[],[]]");

        REQUIRE(rlp.tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&rlp.value.list) == 3);

        unsigned char b[] = {0xBA, 0x95};
        struct minth_rlp_t* e = vector_rlp_t_begin(&rlp.value.list);
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 2);
        REQUIRE(memcmp(vector_uchar_begin(&e->value.byte_array), b, 2) == 0);

        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&e->value.list) == 0);

        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&e->value.list) == 0);
        
    }

    SECTION("[0xDA87,0xE43CAB,[],[[]]],0xFF]") {
        minth_rlp_t_init_from_string(&rlp, "[0xDA87,0xE43CABA,[],[[]],0xFF]");
        
        REQUIRE(rlp.tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&rlp.value.list) == 5);

        unsigned char ba1[] = {0xDA, 0x87};
        struct minth_rlp_t* e = vector_rlp_t_begin(&rlp.value.list);
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 2);
        REQUIRE(memcmp(vector_uchar_begin(&e->value.byte_array), ba1, 2) == 0);

        unsigned char ba2[] = {0xE4, 0x3C, 0xAB, 0xA0};
        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 4);
        REQUIRE(memcmp(vector_uchar_begin(&e->value.byte_array), ba2, 4) == 0);

        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&e->value.list) == 0);
        
        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&e->value.list) == 1);

        struct minth_rlp_t* level = vector_rlp_t_begin(&e->value.list);
        REQUIRE(level->tag == MINTH_RLP_T_LIST);
        REQUIRE(vector_rlp_t_size(&level->value.list) == 0);
        
        unsigned char ba3[] = {0xFF};
        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 1);
        REQUIRE(memcmp(vector_uchar_begin(&e->value.byte_array), ba3, 1) == 0);
    }

}
