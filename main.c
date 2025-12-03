#include <stdio.h>
#include <stdlib.h>

#include "prime_functions.h"
#include "headers/datas_and_structures.h"
#include "headers/hash_functions.h"


int main()
{
    // unsigned long long ids[] = {27,18,29,28,39,13,16};
    // unsigned long long count_ids = sizeof(ids) / sizeof(ids[0]);
    // unsigned long long size_of_hash_table = count_ids * 100 / PACKING_RATE; // if table reachs to packing factor then restored hash table has different result, so we choosing number of size will be less the packing factor
    // AddressSpace* as = init_address_space(size_of_hash_table);
    //
    // for (unsigned long long i = 0; i < count_ids; i++) {
    //     Person* new_person = newRecord(ids[i], 18, "Test User");
    //     force_insert(as, new_person);
    // }

    unsigned long long record_count = 1234;
    AddressSpace* as = init_address_space(record_count); // Reachs to packing factor and will be restored hash table 38 times

    for (unsigned long long i = 0; i < record_count; i++) {
        Person* new_person = newRecord(i + first_prime_number_after(56214), 18, "Test User");
        force_insert(as, new_person);
    }
    print_hash_table(as);
    return 0;
}