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

        struct minth_rlp_t* e = vector_rlp_t_begin(&rlp.value.list);
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 2);

        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 4);

        ++e;
        REQUIRE(e->tag == MINTH_RLP_T_BYTE_ARR);
        REQUIRE(vector_uchar_size(&e->value.byte_array) == 1);

    }
    minth_rlp_t_init_from_string(&rlp, "[0xA393,[],[]]");
    minth_rlp_t_init_from_string(&rlp, "[0xA393,0x843CAB[],[[]]],0xFF]");

    REQUIRE(2==2);
}
