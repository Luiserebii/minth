#include "../../include/eth/rlp.h"
#include "../../include/eth/vector-t.h"
#include <stdio.h>

int main() {
    vector_t list;
    vector_t_init(&list);
    printf("OwO: %lu\n", vector_t_capacity(&list));
}
