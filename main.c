#include <stdio.h>
#include <stdlib.h>

#include "headers/datas_and_structures.h"
#include "headers/hash_functions.h"


int main()
{
    unsigned int record_count = 1213;
    AddressSpace* as = init_address_space(record_count);

    for (unsigned int id = 0; id < record_count; id++) {
        Person* person = newRecord(id, 5, "abcdefgh");
        force_insert(as, person);
    }

    print_hash_table(as);
    return 0;
}