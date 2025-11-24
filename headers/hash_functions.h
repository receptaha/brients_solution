#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

unsigned int hash_1(unsigned long key, unsigned int address_size);
unsigned int hash_2(unsigned long key, unsigned int address_size);

AddressSpace* init_address_space();
void print_hash_table(AddressSpace* as);

#endif
