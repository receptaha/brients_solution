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

    AddressSpace* init_address_space() {
    AddressSpace* as = malloc(sizeof(AddressSpace));
    if (as == NULL) {
        printf("\nAddress Space cannot allocated");
        exit(-1);
    }

    unsigned int smallest_prime_number = first_prime_number_after(1);

    as->hash_table_size = smallest_prime_number;
    as->record_count = 0;
    as->hash_table = malloc(sizeof(Person*) * as->hash_table_size);
    if (as->hash_table == NULL) {
        printf("\nHash Table cannot allocated");
        free(as);
        exit(-1);
    }

    for (unsigned int i = 0; i < as-> hash_table_size; i++) {
        as->hash_table[i] = NULL;
    }
    return as;
}

void print_hash_table(AddressSpace* as) {
    printf("Rigth now there are  : %u records exist\n", as->hash_table_size);

    for (unsigned int i = 0; i < as->hash_table_size; i++) {
        if (as->hash_table[i] != NULL) {
            printf("%u: Record ID: %lu\n", i, as->hash_table[i]->id);
        } else {
            printf("%u: No record here\n", i);
        }
    }
}

Person* newRecord(int id, int age, char* name) {
    Person* new = malloc(sizeof(Person*));

    if (new == NULL) {
        printf("Couldn't allocate enough space for a new record, exiting...\n");
        return 0;
    }

    new -> id = id;
    new -> age = age;
    new -> name = name;

    return new;
}


int spaceFinder(Person* per, AddressSpace* as) {
    int size = as -> hash_table_size;
    int h1 = per -> id % size;
    int h2 = (per -> id / size) + 1;
    int counter = 1;
    int function = (h1 + h2 * counter) % size;

while (as -> hash_table[function] != NULL && counter < size * 2) {
        counter++;
    }

    if (counter >= size * 2) {
        printf("Couldn't find a space in enough time, must expand the whole table\n");
        return 0;
    }



    return counter;
}

void insert(AddressSpace* as, int id, int age, char* name) {

    if (as -> hash_table_size * 0.8 <= as -> record_count) {
        restore_hash_table(as);
        printf("Not enough space to insert, must expand the whole table\n");
        return;
    }


    int size = as -> hash_table_size;
    Person* new = newRecord(id, age, name);
    int h1 = new -> id % size;
    int h2 = new -> id / size + 1;
    Person* old = as -> hash_table[h1];

    if (old != NULL) {
        int newCounter = spaceFinder(new, as);
        int oldCounter = spaceFinder(old, as);

        if (newCounter == 0 || oldCounter == 0) {
            restore_hash_table(as);
            return;
        }

        if (newCounter > oldCounter) {

            int functionOld = (h1 + h2 * oldCounter) % size;

            as -> hash_table[h1] = new;
            as -> hash_table[functionOld] = old;
        }
        else {
            int functionNew = (h1 + h2 * oldCounter) % size;

            as -> hash_table[functionNew] = new;
        }
        return;
    }
    as -> hash_table[h1] = new;
}
