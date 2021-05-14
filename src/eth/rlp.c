#include "../../include/eth/rlp.h"
#include "../../include/eth/vector-t.h"
#include <stdio.h>

int main() {
    vector_rlp_t list;
    vector_rlp_t_init(&list);
    printf("OwO: %lu\n", vector_rlp_t_capacity(&list));
}
