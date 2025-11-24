#include <stdio.h>
#include <stdlib.h>
#include "headers/datas_and_structures.h"
#include "headers/hash_functions.h"


int main()
{
    AddressSpace* as = init_address_space();
    free(as);
    return 0;
}