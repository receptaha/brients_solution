#include <stdio.h>
#include <stdlib.h>
#include "headers/datas_and_structures.h"
#include "headers/hash_functions.h"


int main()
{
    struct AddressSpace* as = init_address_space();
    print_hash_table(as);
    return 0;
}