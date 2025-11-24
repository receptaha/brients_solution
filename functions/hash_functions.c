#include <stdio.h>
#include <stdlib.h>
#include "../headers/datas_and_structures.h"
#include "../headers/prime_functions.h"

unsigned int hash_1(unsigned long key, unsigned int address_size) {
    return key % address_size;
}

unsigned int hash_2(unsigned long key, unsigned int address_size) {
    return key / address_size;
}

struct AddressSpace* init_address_space() {
    struct AddressSpace* as = malloc(sizeof(struct AddressSpace));
    if (as == NULL) {
        printf("\nAddress Space cannot allocated");
        exit(-1);
    }

    unsigned int smallest_prime_number = first_prime_number_after(1);

    as->hash_table_size = smallest_prime_number;
    as->record_count = 0;
    as->hash_table = malloc(sizeof(struct Person*) * as->hash_table_size);
    if (as->hash_table == NULL) {
        printf("\nHash Table cannot allocated");
        free(as);
        exit(-1);
    }

    for (unsigned int i = 0; i < smallest_prime_number; i++) {
        as->hash_table[i] = NULL;
    }
    return as;
}

void print_hash_table(struct AddressSpace* as) {
    printf("Güncel tablo durumu : %u kayıt mevcut\n", as->hash_table_size);

    for (unsigned int i = 0; i < as->hash_table_size; i++) {
        if (as->hash_table[i] != NULL) {
            printf("%u: Kayıt TC: %lu\n", i, as->hash_table[i]->tc);
        } else {
            printf("%u: BOŞ\n", i);
        }
    }
}