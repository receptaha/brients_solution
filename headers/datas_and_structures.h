#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#define PACKING_RATE 0.8

struct Person {
    unsigned long tc;
    unsigned int age;
    char* name;
};

struct AddressSpace {
    unsigned int record_count;
    unsigned int hash_table_size;
    struct Person** hash_table;
};

#endif