#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

unsigned long long hash_1(unsigned long long key, unsigned long long address_size);
unsigned int hash_2(unsigned long long key, unsigned long long address_size);

AddressSpace* init_address_space(unsigned long long size);

void print_hash_table(AddressSpace* as);

void restore_hash_table(AddressSpace* as);
void force_insert(AddressSpace* as, Person* per);

Person* newRecord(unsigned long long id, unsigned int age, char* name);
unsigned long long spaceFinder(Person* per, AddressSpace* as);
int insert(AddressSpace* as, Person* new);
unsigned long long find(AddressSpace* as, unsigned long long id);
#endif
