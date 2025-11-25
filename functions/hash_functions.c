#include <stdio.h>
#include <stdlib.h>
#include "../headers/datas_and_structures.h"
#include "../headers/prime_functions.h"

int insert( AddressSpace* as, int id, int age, char* name); // Added a prototype so we could successfully call insert from restore_hash_table function (Whenever you see thsi, delete it. We don't need this comment)

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

void restore_hash_table(AddressSpace* as) {
    unsigned int new_size = first_prime_number_after(as->hash_table_size * 2);
    unsigned int first_size = as->hash_table_size;
    Person** temp_hash = malloc(sizeof(Person*) * first_size);
    for (int i = 0; i < first_size; i++) {
        temp_hash[i] = as->hash_table[i];
    }
    free(as->hash_table);
    as->hash_table = malloc(sizeof(Person*) * new_size);
    as->hash_table_size = new_size;
    as->record_count = 0;
    for (int i = 0; i < first_size; i++) {
        if (temp_hash[i] != NULL) insert(as, temp_hash[i]->id, temp_hash[i]->age, temp_hash[i]->name);
    }
    free(temp_hash);
}

Person* newRecord(int id, int age, char* name) {
    Person* new = malloc(sizeof(Person));

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

    while (as -> hash_table[function] != NULL && counter != size) {
        counter++;
    }

    if (counter >= size) {
        printf("Couldn't find any space for id : %lu\n", per->id);
        return 0;
}
    return counter;
}


void forceAdd(AddressSpace* as, Person* per) { //Instead of creating a unique function, I've decided to overload the insert function, it should work

    if (per == NULL) {
        printf("Can't insert a null, exiting...");
        exit(-1);
    }

    if (as -> hash_table_size * 0.8 <= as -> record_count) {
        printf("Hash table restoring...\n");
        restore_hash_table(as);
        forceAdd(as, per);
        return;
    }
    int size = as -> hash_table_size;

    int h1 = per -> id % size;
    int h2 = per -> id / size + 1;
    Person* old = as -> hash_table[h1];

    if (old != NULL) {
        int newCounter = spaceFinder (per, as);
        int oldCounter = spaceFinder(old, as);

        if (newCounter == 0 && oldCounter == 0) {
            restore_hash_table(as);
            forceAdd(as, per);
            return;
        }

        if (newCounter > oldCounter) {

            int functionOld = (h1 + h2 * oldCounter) % size;

            as -> hash_table[h1] = per;
            as -> hash_table[functionOld] = old;
        }
        else {
            int functionNew = (h1 + h2 * newCounter) % size;
            as -> hash_table[functionNew] = per;
        }
        as->record_count++;
        return;
    }
    as -> hash_table[h1] = per;
    as->record_count++;
}

int insert(AddressSpace* as, int id, int age, char* name) {

    Person* new = newRecord(id, age, name);
    if (as -> hash_table_size * 0.8 <= as -> record_count) {
        printf("Hash table restoring...\n");
        restore_hash_table(as);
        forceAdd(as, new);
        return 0;
    }

    int size = as -> hash_table_size;
    int h1 = new -> id % size;
    int h2 = new -> id / size + 1;
    Person* old = as -> hash_table[h1];

    if (old != NULL) {
        int newCounter = spaceFinder(new, as);
        int oldCounter = spaceFinder(old, as);

        if (newCounter == 0 && oldCounter == 0) {
            restore_hash_table(as);
            forceAdd(as, new);
            return 0;
        }

        if (newCounter > oldCounter) {

            int functionOld = (h1 + h2 * oldCounter) % size;

            as -> hash_table[h1] = new;
            as -> hash_table[functionOld] = old;
        }
        else {
            int functionNew = (h1 + h2 * newCounter) % size;
            as -> hash_table[functionNew] = new;
        }
        as->record_count++;
        return 1;
    }
    as -> hash_table[h1] = new;
    as->record_count++;
    return 1;
}


