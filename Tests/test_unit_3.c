// test_unit_3.c - Test for initializePokemon() function
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../pokemon.h"

// I face stack  overflow error ...
// use dynamic memory allocation to use HEAP instead of relying only on STACK or use static keyword to use globalized memory
int main()
{

    srand(time(NULL));
    Type *types = malloc(sizeof(Type) * TYPES_COUNT);
    // static Type types[TYPES_COUNT];

    Move *moves = malloc(sizeof(Move) * MOVES_COUNT);
    // static Move moves[MOVES_COUNT];

    Pokemon *pokemons = malloc(sizeof(Pokemon) * POKEMONS_COUNT);
    // static Pokemon pokemons[POKEMONS_COUNT];

    if (types == NULL || moves == NULL || pokemons == NULL)
    {
        printf("Dynamic memory allocation failed for types, moves or pokemons array.\n");
        return 1;
    }

    printf("==============================================\n");
    printf("POKEMON INITIALIZATION TEST\n");
    printf("==============================================\n\n");

    printf("Initializing types...\n");
    initializeTypes(types);
    printf("Types initialization completed.\n\n");

    printf("Initializing moves...\n");
    initializeMoves(moves, types);
    printf("Moves initialization completed.\n\n");

    printf("Initializing pokemons...\n");
    initializePokemons(types, moves, pokemons);
    printf("Pokemons initialization completed.\n\n");

    printf("==============================================\n");
    printf("FIRST 10 POKEMON\n");
    printf("==============================================\n");

    for (int i = 0; i < 10 && i < POKEMONS_COUNT; i++)
    {
        printf("\n--- Pokemon #%d ---\n", i + 1);
        printf("Name: %s\n", pokemons[i].name);
        printf("Types: %s / %s\n",
               pokemons[i].types[0].name,
               pokemons[i].types[1].name);
        printf("HP: %d/%d (Current/Max)\n",
               pokemons[i].currentHP,
               pokemons[i].maxHP);
        printf("Stats: ATK=%d | DEF=%d | SpA=%d | SpD=%d | SPD=%d\n",
               pokemons[i].attack,
               pokemons[i].defense,
               pokemons[i].spAtk,
               pokemons[i].spDef,
               pokemons[i].speed);
        printf("Moves:\n");
        for (int j = 0; j < 4; j++)
        {
            printf("  %d. %-20s [%s] [%s] Power: %.0f\n",
                   j + 1,
                   pokemons[i].moves[j].name,
                   pokemons[i].moves[j].type.name,
                   pokemons[i].moves[j].category == Physical ? "Physical" : "Special",
                   pokemons[i].moves[j].power);
        }
    }

    printf("\n==============================================\n");
    printf("LAST 10 POKEMON\n");
    printf("==============================================\n");

    for (int i = POKEMONS_COUNT - 10; i < POKEMONS_COUNT; i++)
    {
        if (i >= 0)
        {
            printf("\n--- Pokemon #%d ---\n", i + 1);
            printf("Name: %s\n", pokemons[i].name);
            printf("Types: %s / %s\n",
                   pokemons[i].types[0].name,
                   pokemons[i].types[1].name);
            printf("HP: %d/%d (Current/Max)\n",
                   pokemons[i].currentHP,
                   pokemons[i].maxHP);
            printf("Stats: ATK=%d | DEF=%d | SpA=%d | SpD=%d | SPD=%d\n",
                   pokemons[i].attack,
                   pokemons[i].defense,
                   pokemons[i].spAtk,
                   pokemons[i].spDef,
                   pokemons[i].speed);
            printf("Moves:\n");
            for (int j = 0; j < 4; j++)
            {
                printf("  %d. %-20s [%s] [%s] Power: %.0f\n",
                       j + 1,
                       pokemons[i].moves[j].name,
                       pokemons[i].moves[j].type.name,
                       pokemons[i].moves[j].category == Physical ? "Physical" : "Special",
                       pokemons[i].moves[j].power);
            }
        }
    }

    printf("\n==============================================\n");
    printf("POKEMON WITH 'NONE' SECONDARY TYPE\n");
    printf("==============================================\n");

    int noneTypeCount = 0;
    printf("\nSearching for Pokemon with 'None' as secondary type...\n");

    for (int i = 0; i < POKEMONS_COUNT && noneTypeCount < 5; i++)
    {
        if (strcmp(pokemons[i].types[1].name, "None") == 0)
        {
            printf("\n%d. %s - Types: %s / %s\n",
                   noneTypeCount + 1,
                   pokemons[i].name,
                   pokemons[i].types[0].name,
                   pokemons[i].types[1].name);
            noneTypeCount++;
        }
    }

    printf("\n==============================================\n");
    printf("VERIFICATION CHECKS\n");
    printf("==============================================\n");

    // Check 1: Verify currentHP equals maxHP for all Pokemon
    int hpCheckPassed = 1;
    for (int i = 0; i < POKEMONS_COUNT; i++)
    {
        if (pokemons[i].currentHP != pokemons[i].maxHP)
        {
            printf(" FAILED: Pokemon %s has currentHP=%d but maxHP=%d\n",
                   pokemons[i].name,
                   pokemons[i].currentHP,
                   pokemons[i].maxHP);
            hpCheckPassed = 0;
        }
    }
    if (hpCheckPassed)
    {
        printf("All Pokemon have currentHP equal to maxHP\n");
    }

    // Check 2: Verify all Pokemon have 4 unique moves
    int movesCheckPassed = 1;
    for (int i = 0; i < 10; i++) // Check first 10 for brevity
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = j + 1; k < 4; k++)
            {
                if (strcmp(pokemons[i].moves[j].name, pokemons[i].moves[k].name) == 0)
                {
                    printf("FAILED: Pokemon %s has duplicate move: %s\n",
                           pokemons[i].name,
                           pokemons[i].moves[j].name);
                    movesCheckPassed = 0;
                }
            }
        }
    }
    if (movesCheckPassed)
    {
        printf("All checked Pokemon have unique moves\n");
    }

    // Check 3: Verify all Pokemon have valid types
    int typesCheckPassed = 1;
    for (int i = 0; i < POKEMONS_COUNT; i++)
    {
        if (strlen(pokemons[i].types[0].name) == 0 ||
            strlen(pokemons[i].types[1].name) == 0)
        {
            printf("FAILED: Pokemon %s has empty type name\n", pokemons[i].name);
            typesCheckPassed = 0;
        }
    }
    if (typesCheckPassed)
    {
        printf("All Pokemon have valid type names\n");
    }

    // Check 4: Count Pokemon with None type
    int noneCount = 0;
    for (int i = 0; i < POKEMONS_COUNT; i++)
    {
        if (strcmp(pokemons[i].types[1].name, "None") == 0)
        {
            noneCount++;
        }
    }
    printf("Found %d Pokemon with 'None' as secondary type\n", noneCount);

    printf("\n==============================================\n");
    printf("STATISTICS\n");
    printf("==============================================\n");
    printf("Total Pokemon loaded: %d\n", POKEMONS_COUNT);
    printf("Total Types: %d\n", TYPES_COUNT);
    printf("Total Moves: %d\n", MOVES_COUNT);

    // Calculate average stats
    int totalHP = 0, totalAtk = 0, totalDef = 0, totalSpd = 0;
    for (int i = 0; i < POKEMONS_COUNT; i++)
    {
        totalHP += pokemons[i].maxHP;
        totalAtk += pokemons[i].attack;
        totalDef += pokemons[i].defense;
        totalSpd += pokemons[i].speed;
    }

    printf("Average Stats:\n");
    printf("  HP: %d\n", totalHP / POKEMONS_COUNT);
    printf("  Attack: %d\n", totalAtk / POKEMONS_COUNT);
    printf("  Defense: %d\n", totalDef / POKEMONS_COUNT);
    printf("  Speed: %d\n", totalSpd / POKEMONS_COUNT);

    printf("\n==============================================\n");
    printf("TEST COMPLETED SUCCESSFULLY!\n");
    printf("==============================================\n");

    return 0;
}