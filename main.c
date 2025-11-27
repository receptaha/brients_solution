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
    person4->age = 21;
    person4->name = "Mehmet X1";
    force_insert(as, person4);

    Person* person5 = malloc(sizeof(Person));
    person5->id = 15;
    person5->age = 21;
    person5->name = "Mehmet X2";
    force_insert(as, person5);

    Person* person6 = malloc(sizeof(Person));
    person6->id = 19;
    person6->age = 21;
    person6->name = "Mehmet X3";
    force_insert(as, person6);

    Person* person7 = malloc(sizeof(Person));
    person7->id = 12376;
    person7->age = 21;
    person7->name = "Mehmet X4";
    force_insert(as, person7);

    print_hash_table(as);

    get(as, 129387123);

    return 0;
}