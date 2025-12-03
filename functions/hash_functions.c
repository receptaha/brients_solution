#include <stdio.h>
#include <stdlib.h>
#include "../headers/datas_and_structures.h"
#include "../headers/prime_functions.h"
#include "../headers/hash_functions.h"

unsigned long long hash_1(unsigned long long key, unsigned long long address_size) {
    return key % address_size;
}

unsigned int hash_2(unsigned long long key, unsigned long long address_size) {
    return key / address_size + 1;
}

AddressSpace* init_address_space(unsigned long long size) {
    AddressSpace* as = malloc(sizeof(AddressSpace));
    if (as == NULL) {
        printf("\nAddress Space cannot allocated");
        exit(-1);
    }


    as->hash_table_size = is_prime_number(size) ? size : first_prime_number_after(size);
    as->record_count = 0;
    as->hash_table = malloc(sizeof(Person*) * as->hash_table_size);
    if (as->hash_table == NULL) {
        printf("\nHash Table cannot allocated");
        free(as);
        exit(-1);
    }

    for (unsigned long long i = 0; i < as-> hash_table_size; i++) {
        as->hash_table[i] = NULL;
    }
    return as;
}

void print_hash_table(AddressSpace* as) {
    printf("\nTable size : %llu\t Record count : %llu\n", as->hash_table_size, as->record_count);

    for (unsigned long long i = 0; i < as->hash_table_size; i++) {
        if (as->hash_table[i] != NULL) {
            printf("%llu: Record ID: %llu\n", i, as->hash_table[i]->id);
        } else {
            printf("%llu: NULL\n", i);
        }
    }
}

void restore_hash_table(AddressSpace* as) {
    printf("\nHash table is restoring\n");
    unsigned long long new_size = first_prime_number_after(as->hash_table_size);
    unsigned long long first_size = as->hash_table_size;
    Person** temp_hash = malloc(sizeof(Person*) * first_size);
    for (unsigned long long i = 0; i < first_size; i++) {
        temp_hash[i] = as->hash_table[i];
    }
    free(as->hash_table);
    as->hash_table = malloc(sizeof(Person*) * new_size);
    as->hash_table_size = new_size;
    as->record_count = 0;
    for (unsigned long long i = 0; i < new_size; i++) {
        as->hash_table[i] = NULL;
    }
    for (unsigned long long i = 0; i < first_size; i++) {
        if (temp_hash[i] != NULL) {
            force_insert(as, temp_hash[i]);
        }
    }
    free(temp_hash);
}

Person* newRecord(unsigned long long id, unsigned int age, char* name) {
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


unsigned long long spaceFinder(Person* per, AddressSpace* as) {
    unsigned long long size = as -> hash_table_size;
    unsigned long long h1 = hash_1(per->id, size);
    unsigned int h2 = hash_2(per->id, size);
    unsigned long long probe = 0;
    while (as -> hash_table[(h1 + h2 * probe) % size] != NULL && probe != size) {
        probe++;
    }

    if (probe >= size) {
        printf("Couldn't find any space for id : %llu\n", per->id);
        return 0;
}
    return probe;
}

void force_insert(AddressSpace* as, Person* per) {
    if (per == NULL) {
        printf("Person is NULL, exiting...");
        exit(-1);
    }

    unsigned long long address = find(as, per->id);
    if (address != -1) {
        printf("\nID : %llu is already exist on address %llu\n", per->id, address);
        return;
    }

    while (!insert(as, per)) {
        restore_hash_table(as);
    }
    printf("\n" "%llu force inserted\n", per->id);
}

int insert(AddressSpace* as, Person* new) {
    if (as->record_count * 100 / as->hash_table_size > 80) {
        return 0;
    }

    unsigned long long size = as -> hash_table_size;
    unsigned long long index = hash_1(new->id, size);
    unsigned int news_quotient = hash_2(new->id, size);
    Person* old = as -> hash_table[index];

    if (old != NULL) {
        unsigned int olds_quotient = hash_2(old->id, size);
        unsigned long long newCounter = spaceFinder(new, as);
        unsigned long long oldCounter = spaceFinder(old, as);

        if (newCounter == 0 && oldCounter == 0) {
            return 0;
        }

        if (newCounter > oldCounter) {
            as -> hash_table[index] = new;
            as -> hash_table[(index + olds_quotient * oldCounter) % size] = old;
        }
        else {
            as->hash_table[(index + news_quotient * newCounter) % size] = new;
        }
        as->record_count++;
        return 1;
    }
    as -> hash_table[index] = new;
    as->record_count++;
    return 1;
}

unsigned long long find(AddressSpace* as, unsigned long long id) {
    unsigned long long index = hash_1(id, as->hash_table_size);
    unsigned int quotient = hash_2(id, as->hash_table_size);
    unsigned int counter = 0;

    while (counter < as->hash_table_size) {

        if (as->hash_table[index] == NULL) {
            counter++;
            continue;
        }

        if (as->hash_table[index]->id == id) {
            break;
        }

        counter++;
        index = (index + quotient) % as->hash_table_size;
    }

    if (counter >= as->hash_table_size) {
        return -1;
    }
    return index;
}


