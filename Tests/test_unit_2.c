// this unit will test move initialization function in pokemon.c
#include <stdio.h>
#include "..\\pokemon.h"
// pokemon.h includes functions prototypes while pokemon.c includes their implementation

int main()
{
    Type types[TYPES_COUNT];
    Move moves[MOVES_COUNT];

    printf("Initializing types...\n");
    initializeTypes(types);

    printf("types initialization completed.\n");

    printf("Initializing moves...\n");
    initializeMoves(moves, types);
    printf("moves initialization completed.\n");
    
    // print first 10 moves to verify they are initialized correctly

    for (int i = 0; i < 10; i++)
    {
        printf("Move Name: %s, Type: %s, Category: %d, Power: %.2f\n", moves[i].name, moves[i].type.name, moves[i].category, moves[i].power);
    }
    printf("---------------------------------------------------\n");
    // print last 10 moves to verify they are initialized correctly
    for (int i = MOVES_COUNT - 10; i < MOVES_COUNT; i++)
    {
        printf("Move Name: %s, Type: %s, Category: %d, Power: %.2f\n", moves[i].name, moves[i].type.name, moves[i].category, moves[i].power);
    }

    printf("Move initialization test completed.\n");
}