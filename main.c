#include <stdio.h>
#include <stdlib.h>
#include "headers/datas_and_structures.h"
#include "headers/hash_functions.h"


int main()
{
    AddressSpace* as = init_address_space();
    Person* person1 = malloc(sizeof(Person));
    person1->id = 3;
    person1->age = 25;
    person1->name = "Recep Taha Ayvaz";
    force_insert(as, person1);

    Person* person2 = malloc(sizeof(Person));
    person2->id = 4;
    person2->age = 21;
    person2->name = "Cihan Şahin";
    force_insert(as, person2);

    Person* person3 = malloc(sizeof(Person));
    person3->id = 5;
    person3->age = 25;
    person3->name = "Alper Yıldırım";
    force_insert(as, person3);

    Person* person4 = malloc(sizeof(Person));
    person4->id = 8;
    person4->age = 25;
    person4->name = "Ilgın Geçgel";
    force_insert(as, person4);

    print_hash_table(as);

    get(as, 8);
    return 0;
}