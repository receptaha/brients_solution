#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H
#define PACKING_RATE 0.8

typedef struct Person {
    unsigned long id;
    unsigned int age;
    char* name;
}Person;

typedef struct AddressSpace {
    unsigned int record_count;
    unsigned int hash_table_size;
    Person** hash_table;
}AddressSpace;

#endif