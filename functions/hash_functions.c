#include "../headers/hash_functions.h"
unsigned int hash_1(unsigned long key, unsigned int address_size) {
    return key % address_size;
}

unsigned int hash_2(unsigned long key, unsigned int address_size) {
    return key / address_size;
}